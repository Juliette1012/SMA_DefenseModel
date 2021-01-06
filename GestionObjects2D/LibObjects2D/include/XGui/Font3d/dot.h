  default: //  '.'
    {
    static double pointArray_dot[]=
      { 0 , 0.079626 , 0.5,
        0 , 0.0135482 , 0.5,
        0.0629594 , 0.0135482 , 0.5,
        0.0629594 , 0.079626 , 0.5,
        0 , 0.079626 , -0.5,
        0.0629594 , 0.0135482 , -0.5,
        0 , 0.0135482 , -0.5,
        0.0629594 , 0.079626 , -0.5 };
    pointArray=pointArray_dot;
    nbPoints=8;
    static int faceArray_dot[]=
      { 0 , 1 , 2,
        0 , 2 , 3,
        4 , 5 , 6,
        4 , 7 , 5,
        1 , 0 , 4,
        1 , 4 , 6,
        2 , 1 , 6,
        2 , 6 , 5,
        3 , 2 , 5,
        3 , 5 , 7,
        0 , 3 , 7,
        0 , 7 , 4 };
    faceArray=faceArray_dot;
    nbFaces=12;
    advance=0.0629594;
    }
    break;
