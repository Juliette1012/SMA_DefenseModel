  case '-':
    {
    static double pointArray_minus[]=
      { 0 , 0.25059 , -0.5,
        0 , 0.175192 , -0.5,
        0 , 0.175192 , 0.5,
        0 , 0.25059 , 0.5,
        0.283854 , 0.25059 , -0.5,
        0.283854 , 0.25059 , 0.5,
        0.283854 , 0.175192 , -0.5,
        0.283854 , 0.175192 , 0.5 };
    pointArray=pointArray_minus;
    nbPoints=8;
    static int faceArray_minus[]=
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
    faceArray=faceArray_minus;
    nbFaces=12;
    advance=0.283854;
    }
    break;
