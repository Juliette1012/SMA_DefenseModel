  case '/':
    {
    static double pointArray_slash[]=
      { 0.248372 , 0.465698 , -0.5,
        0.195842 , 0.465698 , -0.5,
        0.195842 , 0.465698 , 0.5,
        0.248372 , 0.465698 , 0.5,
        0.0525298 , -0.039916 , -0.5,
        0.0525298 , -0.039916 , 0.5,
        0 , -0.039916 , -0.5,
        0 , -0.039916 , 0.5 };
    pointArray=pointArray_slash;
    nbPoints=8;
    static int faceArray_slash[]=
      { 0 , 1 , 2,
        0 , 2 , 3,
        4 , 0 , 3,
        4 , 3 , 5,
        6 , 4 , 5,
        6 , 5 , 7,
        1 , 6 , 7,
        1 , 7 , 2,
        2 , 7 , 5,
        4 , 6 , 1,
        2 , 5 , 3,
        0 , 4 , 1 };
    faceArray=faceArray_slash;
    nbFaces=12;
    advance=0.248372;
    }
    break;
