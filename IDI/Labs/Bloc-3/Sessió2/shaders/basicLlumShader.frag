#version 330 core

vec3 fcolor;
out vec4 FragColor;

in vec3 fvertex;
in vec3 fnormal;

in vec3 fmatamb;
in vec3 fmatdiff;
in vec3 fmatspec;
in float fmatshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

uniform vec3 posFocus;
uniform bool type;

// Valors per als components que necessitem del focus de llum
vec3 colorFocus = vec3(0.8, 0.8, 0.8);
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

vec3 Ambient() {
    return llumAmbient * fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * fmatdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), fmatshin);
    return (fmatspec * colFocus * shine); 
}

void main()
{	
  /*
	vec3 newPosFocus = (vec4(posFocus, 1) * view).xyz;

	mat3 NormalMatrix = inverse(transpose(mat3(view*TG)));

	vec3 NormSCO = normalize(NormalMatrix * fnormal);

	vec4 vertSCO = (view * TG * vec4(fvertex, 1.0));

	vec3 L = normalize((view * vec4(newPosFocus, 1.0)).xyz - vertSCO.xyz);
	*/

	vec4 posSCO = vec4(posFocus,1.0);
	
	if (type) posSCO = view* posSCO;

	vec4 vertSCO = (view * TG * vec4(fvertex, 1.0));
	
	vec4 L = posSCO - vertSCO;

	vec3 L_SCO = L.xyz;

	L_SCO = normalize(L_SCO);

	mat3 NormalMatrix = inverse(transpose(mat3(view*TG)));
	vec3 NormSCO = normalize(NormalMatrix * fnormal);

	vec3 fcolor = Ambient() + Difus(NormSCO, L_SCO, colorFocus) + Especular(NormSCO, L_SCO, vertSCO, colorFocus);
	
	FragColor = vec4(fcolor,1);	
}
