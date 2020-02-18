xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Material lambert2 {
 1.000000;1.000000;1.000000;1.000000;;
 0.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "e_tex.png";
 }
}

Frame e {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame pCube1 {
  

  FrameTransformMatrix {
   9.753894,0.000000,0.000000,0.000000,0.000000,-0.000000,-9.354374,0.000000,0.000000,9.354374,-0.000000,0.000000,-0.000001,0.000000,-4.376845,1.000000;;
  }

  Mesh pCube1 {
   8;
   -0.417712;-0.439517;-0.399840;,
   0.417712;-0.439517;0.716895;,
   0.417712;-0.439517;-0.399840;,
   -0.417712;-0.439517;0.716895;,
   0.441895;-0.496269;0.749221;,
   -0.441895;-0.496269;0.749221;,
   -0.441895;-0.496269;-0.432166;,
   0.441895;-0.496269;-0.432166;;
   10;
   3;0,1,2;,
   3;1,0,3;,
   3;3,4,1;,
   3;4,3,5;,
   3;6,2,7;,
   3;2,6,0;,
   3;2,4,7;,
   3;4,2,1;,
   3;6,3,0;,
   3;3,6,5;;

   MeshNormals {
    8;
    -0.084512;0.994658;-0.059280;,
    0.084512;0.994658;0.059280;,
    0.084512;0.994658;-0.059280;,
    -0.084512;0.994658;0.059280;,
    0.630764;0.569192;0.527406;,
    -0.630764;0.569192;0.527406;,
    -0.630764;0.569193;-0.527406;,
    0.630763;0.569193;-0.527406;;
    10;
    3;0,1,2;,
    3;1,0,3;,
    3;3,4,1;,
    3;4,3,5;,
    3;6,2,7;,
    3;2,6,0;,
    3;2,4,7;,
    3;4,2,1;,
    3;6,3,0;,
    3;3,6,5;;
   }

   MeshMaterialList {
    1;
    10;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;
    { lambert2 }
   }

   MeshTextureCoords c1 {
    8;
    0.147408;0.951825;,
    0.845138;0.048175;,
    0.843715;0.949989;,
    0.148830;0.050010;,
    0.889103;0.004348;,
    0.103894;0.004408;,
    0.103444;0.995652;,
    0.888653;0.995592;;
   }
  }
 }
}