  case ',':
    {
    static double pointArray_coma[]=
      { 0 , -0.0427583 , -0.5,
        0.0363827 , -0.057658 , -0.5,
        0.0363827 , -0.057658 , 0.5,
        0 , -0.0427583 , 0.5,
        0.0541234 , 0.088704 , -0.5,
        0.0541234 , 0.088704 , 0.5,
        0.115316 , 0.063341 , -0.5,
        0.115316 , 0.063341 , 0.5 };
    pointArray=pointArray_coma;
    nbPoints=8;
    static int faceArray_coma[]=
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
    faceArray=faceArray_coma;
    nbFaces=12;
    advance=0.115316;
    }
    break;
