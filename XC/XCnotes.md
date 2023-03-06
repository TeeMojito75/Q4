# Unit 1 - introduction

yada yada I'll type something here one day

# Unit 2 - IP


## IP addresses

**Internet Protocol** (IP) goal is *routing datagrams*

**Characteristics:**

- Connectionless
- Stateless
- Best effort

4 bytes of information (32 bits). Separated between **NETID** (identifies a network) and **HOSTID** (identifies a host in that network)

We use dotted point notation, therefore separating bytes with dots. An example would be *224.0.0.1*.

- An address identifies an interface
- All addresses in an IP net share the same netid
- All assigned addresses must be different (either host or net must change)
- Internet Assigned Numbers Authority (IANA) assing IP addresses to Regional Internet Registries (RIR)
- These RIRs assign addresses to Internet Service Providers (ISP), and ISPs to their customers

- IPv6, the solution to IPv4 run out
	+ 16 bytes of information, in eight groups of two bytes in hexadecimal
	

## IPv4 Address classes

It is a mechanism defined at the start of the internet to know the number of bytes in the hostid and netid.

**Characteristics:**

- All IPv4 addresses belong to a particular class, with varying netid/hostid bytes in classes A/B/C 
- D class is for **multicast addresses** (an entire group of addresses)
	+ e.g. 224.0.0.2: "all routers"
- E class are reserved addresses
- **Most Significant Bits (MSB) identify the class**


| Class | netid | hostid | MSB       | range             |
|-------|-------|--------|-----------|-------------------|
|   A   |     1 |      3 | 0xxx...x  | 0.0.0.0~          |
|   B   |     2 |      2 | 10xx...x  | 128.0.0.0~        |
|   C   |     3 |      1 | 110x...x  | 192.0.0.0~        |
|   D   |     - |      - | 1110...x  | 224.0.0.0~        |
|   E   |     - |      - | 1111...x  | 240.0.0.0~        |


### Special addresses

These addresses have special meanings and cannot be assigned to an interface. All IP networks have 2 special addresses, those being the **Network address** and the **Broadcast address**.

| netid | hostid | 					Meaning
|-------|--------|-------------------------------------------|
|  any  |  all 0 | Network address // Used in routing tables |
|  any  |  all 1 | Broadcast addresses						 |
| all 0 |  all 0 | This host in this net. Source IP in DCHP  |
| all 1 |  all 1 | Broadcast in this net. Dest IP in DHCP    |
|  127  |   any	 | Host loopback							 |


### Private addresses

These are for private use only (not routable in the Internet).

- Not unique
- Not assigned to any RIR

| Class | nets  | hosts  | Addresses					 |
|-------|-------|--------|-------------------------------|
|   A   |     1 |  2^24  | 10.0.0.0          			 |
|   B   |    16 |  2^16  | 172.16.0.0 ~ 172.31.0.0       |
|   C   |   256 |  2^8   | 192.168.0.0 ~ 192.168.255.0   |


### Subnetting - RFC 950

Subnetting consists on spliting a large network into smaller ones. 
To begin, we use a **Network mask** to identify the number of bits our netid has:

**Example:** 147.84.22.3/**24** (notation in bits)

Usually these 24 bits will be the most significant ones, so the mask in dotted notation will look something like this: 255.255.255.0 -> 11111111 11111111 11111111 00000000

#### An example

Let us say we have a C class net, such that its IP address is 200.200.200.0/24 (24 being the bits of the netid). However, we want 4 subnets, how do we do this? **We take the 2 Most Significant Bits of the hostid**. Now, our IP looks like this: 200.200.200.0/26. Now, our netid spans 6 bits (up to 64 values). If we want to use all 256 addresses, we need to split them in 4 subnets.

|  subnetid  |  subnet  |   range       |   broadcast    |  available addresses  |
|------------|----------|---------------|----------------|-----------------------|
|     00     |   B.0/26 |    B.0 ~ B.63 |      B.63      |     2⁶ - 2  = 62      |
|     01     |  B.64/26 |  B.64 ~ B.127 |      B.127     |     2⁶ - 2  = 62      |
|     10     | B.128/26 | B.128 ~ B.191 |      B.191     |     2⁶ - 2  = 62      |
|     11     | B.192/26 | B.192 ~ B.255 |      B.255     |     2⁶ - 2  = 62      |


It is possible that we need to divide these subnets in smaller portions, and we can do so thanks to these network masks being of variable size. The only thing we need to keep in mind is that **net ranges must not be superposed**.


|  subnetid  |  subnet  |   range       |   broadcast    |  available addresses  |
|------------|----------|---------------|----------------|-----------------------|
|     00     |   B.0/26 |    B.0 ~ B.63 |      B.63      |     2⁶ - 2  = 62      |
|     01     |  B.64/26 |  B.64 ~ B.127 |      B.127     |     2⁶ - 2  = 62      |
|     10     | B.128/26 | B.128 ~ B.191 |      B.191     |     2⁶ - 2  = 62      |
|     110    | B.192/27 | B.192 ~ B.223 |      B.223     |     2⁵ - 2  = 30      |
|     111    | B.224/27 | B.224 ~ B.255 |      B.255     |     2⁵ - 2  = 30      |


### Routing table (RT)

Contains the destinations it can arrive to in the IP layer. Discards datagrams if they're not on the table.

- **IP layer** in hosts and routers
- ip_output() routs datagrams thanks to it
- DIrect Routing: destination directly corrected
- Indirect Routing: sent to a gateway
- Default route: 0.0.0.0./0 matches the whole IPv4 address space

#### Routing info

If we type "route -n" in the terminal we can check the different relevant columns in our routing table. We can divide them in two groups:

**Destination:** Network and mask
**How to reach them:** Gateway and interface (Iface)

Gateway contains the address of the router used to direct the datagram to its destination. Therefore, it is the IP address of a routed from a directly connected network. Its value is 0.0.0.0 if the routing is direct.

Iface identifies an interface through which we must send the datagram.

To check if our routing table has a valid destination for our datagram, a bitwise AND is done using its destination address and the routing table entry's genmask. If it coincides with the entry's destination IP, we can use that network for routing.


Routing tables are ordered from longest to shortest netid (Longest Prefix Match)

Datagram delivery algorithm:

```C++

	if (IP.destination == address_any_interface) {
		send to loopback interface
	}

	for (RT = each_routing_table_entry) {
		if ((IP.destination & RT.mask) == RT.destination) {
			return(RT.gateway, RT.interface);
		}
	}

	if (RT.gateway == 0.0.0.0) {	// direct routing
		send datagram to IP.destination in RT.interface
	}
	else {							// indirect routing
		send the datagram to RT.gateway in RT.interface
	}

```


## ARP protocol - RFC826

Physical networks use addresses (Ethernet), we need a protocol to 

MAC - Medium Access Control
NIC - Network Interface Card
ARP - Address Resolution Protocol


### Ethernet

**Basic explanation:**

Ethernet uses a *shared medium* that works as a bus. It sends a data packet to all stations connected to the ethernet network. Each of these stations recieves this same data packet. All stations will look at the destination address of this packet. If the address is the one in that computer, it'll interrupt its CPU to transfer this same data through DMA to the computer's memory. Discards this packet otherwise.

If a computer wants to send data through ethernet, it first has to send to the controlling driver the data to send (an IP datagram, for example), aswell as the destination address.


### How ARP works

Knowing we need a physical address to enroute, ARP is needed to convert IP addresses into physical ones. These physical addresses are not always needed, however (point-to-point links, for example, only have one possible destination).

- IP determines the IP address by which to send the datagram (be it the datagram destination or a router, depending on an direct or indirect routing)
- If a physical address isn't needed, then IP will send the datagram to the *driver* for transmission, otherwise:
	+ IP requests ARP the corresponding physical address
	+ ARP may already have the physical address saved in a tuple or will begin the *resolution process*. Will then return to IP the converted address
	+ While waiting for ARP, IP will save the data in a *buffer*, if a time-out happens, the data will be discarded
	+ When ARP answers back, IP sends the datagram to the driver along with the physical address for it to be sent
	

### The resolution process

Let us have 2 host stations, A & B, A wanting to solve B's address. Both ARP caches are empty on boot.

- Station A send an *ARP Request* with an Ethernet address. It's sent to the broadcast, and therefore all CPU's in the network will interrupt the CPU when recieving the message.
- Station B sends an *ARP Reply* to signal that it's trying to solve its address. In this case, this destination is **unicast**, since only A is recieving it. Other computers in the network will discard this message.
- Both caches will be updated with the corresponding IP and Ethernet addresses ( {IPb ; ETHb} & {IPa ; ETHa}, respectively). Caches must be kept small to allow for fast lookups (it must be checked everytime a datagram is sent).

All cache entries have a time-out period. If an entry is used, its time-out resets. If a time-out is reached, the entry will be deleted.