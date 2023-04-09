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

### Format dels missatges ARP

- **Hardware type:** Indica el tipus d'adreça física (Ethernet)
- **Protocol type:** Indica el protocol de l'adreça que es vol resoldre (IPv4)
- **Hard. Lenght:** Indica el nombre de bytes de l'adreça física
- **Prot Lenght:** Indica el nombre de bytes de l'adreça que es vol resoldre (IPv4)
- **Opcode:** Tipus de missatge (Request/Reply)
- **Sender hardware address/server protocol address:** adreça física i del protocol que es vol resoldre, del que envia. En el reply hi ha l'adreça física buscada
- **Targer hardware address/target protocol address:** adreça física i del protocol que es vol resoldre, de l'estació on s'envia. En el request el camp target hardware address és irrellevant

### Gratuitous ARP

 Consisteix en un ARP request que envia un host per resoldre la seva mateixa adreça després de la fase de boot.

 **Motius:**
 - Per detectar adreces IP duplicades en la mateixa xarxa
 - Per actualitzar les caches ARP


### 2.6 Internet Control Message Protocol (ICMP)
 
 Senyalitza missatges d'error o atenció. Característques:

 - Va sobre IP
 - Els pot activar IP/TCP/UDP o un procés de l'usuari
 - Poden ser query o error
 - Els missatges ICMP d'error no poden generar més missatges (per evitar bucles)

 Els camps del missatge són: Type/Code/Checksum/contingut

 A més:
 - Els missatges de tipus query porten un camp anomenat identifier que serveix per poder fer correspondre els request amb els reply

 - Els missatges d'error retornen sempre la capçalera IP del datagrama causant del missatge i els 8 primers bytes del seu payload. Si el datagrama causant de l'error porta encapsulat un segment TCP o un datagrama UDP, els ports origen i destinació queden inclosos en aquests primers 8 bytes. (Info necessària en alguns casos)


### 2.7 Dynamic Host Configuration Protocol (DHCP)

L'assignació d'una adreça IP pot ser manual o automàtica (ifconfig o propi DHCP respectivament)

DHCP és un protocol que segueix el model client-servidor amb l'objectiu de subministrar als clients:

- Paràmetres per a la configuració de la xaraxa
- Assignació temporal o permanent d'adreces IP

L'assignació d'adreces IP pot ser:
- **Dinàmica:** En el servidor s'especifica un conjunt d'adreces IP que es poden assignar als clients i un temps de "lloguer"
- **Automàtica:** El temps de lloguer és il·limitat
- **Manual:** En el servidor s'especifica l'adreça de cada client

Detalls del protocol: Fa servir UDP

1- El client envia un missatge DHCPDISCOVER amb IP font 0.0.0.0 i destinació broadcast 255.255.255.255, port UDP font 68 i destinació 67. Aquest missatge pot sugerir les opcions que desitgi el client, com ara l'adreça IP i el temps de leasing

2- Cada servidor respon amb un missatge DHCPOFFER amb l'oferta dels paràmetres de configuració. Un dels paràmetres és un identificador del servidor

3- El client respon amb un missatge DHCPREQUEST broadcast amb l'identificador del servidor que hi havia en el missatge DHCPOFFER que ha escollit

4- El servidor escollit confirma la configuració enviant un DHCPACK

*Si el client recorda l'adreça IP assignada a una sessió anterior, pot enviar directament un missatge DHCREQUEST. El client també por enviar un DHCPREQUEST per prolongar el temps de leasing


### 2.8 Network address translation (NAT)

La motivació és aprofitar millor les adreces públiques

Funcionament: En l'interiror de la xarxa privada els hosts tenen adreces privades. Amb aquestes adreces les estacions no poden accedir a Internet. LLavors el router NAT ha de fer el següent:
- Als datagrames que surten de la xarxa privada els canvia l'adreça font provada per una adreça pública (adreça de l'ISP)
- Als datagrames qe entren a la xarxa privada en resposta als datagrames anteriors els desf+a el canvi. És a dir, canvia l'adreça destinació pública per l'adreça destinació privada del host

Els canvis són transparents als hosts. Per poder desfer els canvis, els router manté una "Taula NAT" amb les adreces privades i les corresponents adreces públiques

Avantatges:
Estalvia adreces públiques; no hem d'esperar a tenir un ISP per assignar adreces a la xarxa privada; no han de reassignar-se les adreces privades si es canvia l'ISP; afegeix seguretat

Tipus de translacions:

- NAT estàtic: S'associa una adreça pública per a cada adreça privada. 
- NAT dinàmic: Hi ha un conjunt d'adreces púcliques que s'assignen dinàmicament: quan un host inicia una connexió amb internet, s'afegeix una entrada en la taula NAT amb la seva adreça privada i l'adreça pública assignada. La taula té un temporitzador per borrar les entrades inutilitzades i que les adreces tornin a la pool

### PAT

Es fa servir quan volem que més d'un host usi la mateixa adreça pública simultàneament.
Funcionament: quan un host inicia connexió a Internet -> tupla (adreça privada, port local), (adreça pública, port extern) a la taula NAT. Quan un datagrama surt es busca en la taula NAT fent servir (adreça privada, port local). Quan entra s'usa (adreça pública, port extern). D'aquesta forma, totes les tuples (adreça privada, port local) són diferents, encara que poden ser canviada en alguns casos

### DNAT

Mateix funcionament que el mecanisme NAT, però l'objectiu és fer accessible un servidor des d'Internet. 
La iniciativa és d'un client extern, i primer es canviarà l'adreça destinació, perquè els datagramees del client pugin entrar a la xarxa interna. La configuració del DNAT ha de ser estàtica per tanir les assignacións de adreces públic/privades pre-establertes al temps de l'accés.

### Domain name System (DNS)

Objectiu: permet que els usuaris d'internet puguin fer servir noms en comptes d'adreces IP
- Segueix el paradigma client/servidor amb nivell de transport TCP/UDP amb port well_known 53
- Hi ha una base de dades amb els noms i les adreces per poder fer la resolució
- El sistema de noms està organitzat en una jerarquia que permet distribuir la base de dades arreu d'Internet, en comptes d'haver de mantenir-la centralitzada en un únic servidor

La jerarquia està organitzada en "dominis" o "zones". El domini arrel no té nom i d'ell pengen els top levels domain (TLD). Cada un dels TLD té un administrador que delega part del domini en "sub-dominis". Per exemple del TLD *edu* pengen universitats. (exemple rogent.ac.upc.edu)

Cada administrador d'un domini ha de mantenir part de la base de dades de DNS en un servidor primari i un o més de secundaris.

## Accés a la base de dades de DNS

Procediment:
- El host envia el nom que es vol resoldre al seu seridor de DNS
- El seridor envia la petició a un root-server, que li retorna l'adreça del servidro de noms del TLD, domini com
- Després el servidor s'adreça al servidor del com, que retorna l'adreça del servidor de noms del *second level domain*
- Després el servidor s'adreça al servidor del domini foo.com, que li retorna l'adreça buscada
- Finalment el servidor retorna l'adreça buscada al host que ho havia sol·licitat

## Format dels missatges de DNS

Tots els missatges de DNS tenen els camps: Header(especifica missatge)/Question(especifica el que es vol resoldre)/Answer(especifica la resposta)/Authority(especifica el nom de l'autoritat del domini)/Additional(Info adicional)

-**HEADER:** El camp Identification permet relacionar els missatges de query i reply. Els flags més importants són:
 - Query-response: indica si el paquet és de query o reply
 - Authoritative Answer: Indica si ha respost l'autoritat del domini, o si la resposta estava en la cache del servidor on s'ha fet la pregunta
 - Recursion-desired: indica si es desitja que la resolució sigui recursiva

-**Question:** 
 - QName: especifica el nom que es vol resoldre
 - Qtype: especifica el tipus de pregunta
 - QClass: Especifica el tipus d'adreça que es vol resoldre. si es internet == 1

-**Resource Records:** Els camps Answer, Authority i Additional estan format per seq d'un o més RR:
 - Els tres primers camps (Name, type, class) tenen el mateix significat que a Question
 - TTL (time to live) és el nombre de segons que es pot guardar l'RR en cache
 - RDLength: mida del camp Rdata
 - Rdata: és l'adreça IP si el RR és del tipus A o el nom autoritat és del tipus NS


### Algorismes d'encaminament

Tenen per objectiu afegir entrades a la taula d'encaminament. Poden ser:
    - **Estàtics**: entrades afegides manualment o per un protocol/script de configuració com DHCP. Un cop establertes no canvien el seu valor
    - **Adaptatius**: hi ha protocol encaminament encarregat de calcular i afegir les entrades a la taula. El protocol s'estableix entre routers

*Concepte de sistema autònom:
    - Interior gateway Protocol(IGP): El protocol d'encaminament s'estableix entre els routers d'un mateix AS (Millor encaminament possible) (ex: RIP/OSPF)
    - Exterior gateway Protocol(EGP): El protocol d'encaminament s'estableix entre routes de diferent AS (Ús de polítiques d'encaminament) (ex: BGP)

### Routing Information Protocol (RIP)

Característiques:
 - Mètrica == nombre de salts fins destinació
 - Routers envien periòdicament missatge RIP amb les destinacions i mètriques conegudes. UDP i port font/destinació 520
 - Si es deixen de rebre RIP d'un router veí, aleshores s'assumeix que el router veí ha "caigut" i les entrades que el fan servir de gateway es posen amb mètrica infinit (16)
 - EL RIP v2 afegeix la màscara a les destinacions.

* Mirar llibret per funcionament d'actualització taules d'encaminament p33

**Count to infinity**:
mirar p34 per explicació

**Split horizon**:
RIP modifica els missatges de forma que quan fa un broadcast en una interfície, elimina les entrades que tinguin uj gateway en la mateixa interfície. Encara i així, això no resol completament el problema de count to infinity

### Open Shortest Path First (OSPF)
Usat en xarxes grans envers RIP
Funcionament:
 - Els routers mantenen una base de dades amb l'estat de tota la xarxa
 - Cada router monitoritza les xarxes directament connectades i dels seus veïns. Aquesta info s'envia a la resta de routers de la xarxa (només adreces directament connectades)
 - Els LSA necessiten un encaminament especial perquè arribin a tots els routers de la xarxa. S'anomena flooding i consistei en enviar els LSA per totes les interfícies
 - Els missatges OSPF van encapsulats directament sobre IP, camp IP == 89
 - Missatges LSA(Link state advertisements) no s'envien periòdicament
 - Els routers executen un protocol de hello per descobrir i mantenir la relació dels routers veïns. Si un router cau ho detecta per abscència de hello
 - Tots els routers guarden la info rebuda en el link state data-base i fan servir SPF(Dijkstra) per calcular les taules òptimes
 - OSPF no té problema amb count to infinity

### Border Gateway Protocol (BGP)
Protocol d'encaminament EGP, fa servir sistemes autònoms (AS).
Cada AS té un identificador únic de 16 bits anomenat Autonomus System Number (ASN)
El tràfic d'AS es classifica en: 
 - Tràfic local: és el tràfic que s'origina o acaba en el AS
 - Tràfic de trànsit: en cas contrari

En funció del tipus de tràfic, BGP defineix el model:
  - stub AS: que només té una connexió a un altre AS. Òbviament, només té tràfic local
  - multihomed AS: AS que té connexions a més d'un AS, però només porta tràfic local
  - transit AS: AS que té connexions a més d'un AS i que suporta tràfic de trànsit

Funcionament bàsic BGP:
  - Entre cada parell routers BGP veïns s'estableix una connexió punt a punt (TCP) a port 179
  - Cada router BGP envia als seus veïns les xarxes destinació per a les quals vol encaminar tràfic. Per a cada xarxa destinació, BGP envia la llista d'ASN pels que sap que ha de passar per arribar-hi. Això permet a BGP evitar bucles i el problema de count to infinity
  - Amb els missatges que s'intercanvien, els routers BGP van aprenent els ASN i les possibles destinacions d'Internet. ELs missatges BGP també tenen altres atributs que depenen de les routing pilicies. També es fan servir mecanismes d'agregació de rutes per reduir el nombre de destinacions. Els routers BGP guarden informació que reben dels seus peers en una *Routing Information Base*. Amb tot això BGP calcula les entrades que s'afegeixen a la taula d'encaminament

### Seguretat en xarxes IP

Els principals objectius de la seguretat en una xarxa són: Confidencialitat, integritat i diponibilitat

Les vulnerabilitats d'una xarxa poden tenir diferents orígens: tecnològics, de configuració i falta de polítiques de seguretat

Els tipus d'atacs poden ser: de reconeixement, que tenen com a objectiu trobar vulnerabilitats a la xarxa i és el pas previ a un atac; accés d'un intrús a un compte o servei; denegació de servei, que té com a objectiu deshabilitar o corrompre un servei o xarxa i cucs, virus i troyans, sw maliciós que s'autoreplica, danya o corromp el sistema

### Firewalls

Un tallafocs és un dispositiu que separa una xarxa que es vol protegit. Hi ha diferent tipus de firewalls: alguns simples que filtren per IP o ports i altres que són capaços de seguir i filtrar segons l'estat de les connexions i els missatges a nivell d'aplicació.

Els firewalls flitren els paquets que vénen de l'exterior i no compleixen certes condicions. El flitrat es da amb "llistes de control d'accés". Les ACL s'apliquen a l'entrada o sortida d'una interfície. Quan es compleix alguna de les regles el datagrama s'accepta o descarta

mirar p38 per més info

### VPN
Permeten proveir connectivitat a usuaris o xarxes remots com si estiguessin connectats a la xarxa interna.
Perquè la VPN sigui segura s'usa:
  - Autentificació: per reconèixer els usuaris
  - Encriptació: per evitar eavesdropping
  - Túnels: per aïllar els enllaços remots de la resta d'Internet


