#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

uniform mat4 TG;
uniform mat4 TGdisco;
uniform mat4 Proj;
uniform mat4 View;

out vec4 FragColor;

const vec3 llumAmbient = vec3(0.1, 0.1, 0.1);
//const vec3 colEscena = vec3(0.4, 0.4, 0.4);

uniform vec3 posEscena;
uniform vec3 posR;
uniform vec3 posG;
uniform vec3 posB;
uniform vec3 posY;

uniform vec3 colEscena;
uniform vec3 colR;
uniform vec3 colG;
uniform vec3 colB;
uniform vec3 colY;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{   
  vec3 L = posEscena - fvertex;
  L = normalize(L);

  vec3 L1 = posR - fvertex;
  L1 = normalize(L1);

  vec3 L2 = posG - fvertex;
  L2 = normalize(L2);

  vec3 L3 = posB - fvertex;
  L3 = normalize(L3);

  vec3 L4 = posY - fvertex;
  L4 = normalize(L4);

  vec3 NormSCO = normalize(fnormal);

  vec3 fcolor = Ambient() + Difus(NormSCO, L, colEscena) + Especular(NormSCO, L, fvertex, colEscena);
  fcolor += Difus(NormSCO, L1, colR) + Especular(NormSCO, L1, fvertex, colR);
  fcolor += Difus(NormSCO, L2, colG) + Especular(NormSCO, L2, fvertex, colG);
  fcolor += Difus(NormSCO, L3, colB) + Especular(NormSCO, L3, fvertex, colB);
  fcolor += Difus(NormSCO, L4, colY) + Especular(NormSCO, L4, fvertex, colY);

  FragColor = vec4(fcolor, 1);
}