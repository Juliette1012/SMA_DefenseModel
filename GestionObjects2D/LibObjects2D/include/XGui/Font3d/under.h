  case '_':
    {
    static double pointArray_under[]=
      { 0 , -0.0310466 , -0.5,
        0.301595 , -0.0310466 , -0.5,
        0.301595 , -0.0310466 , 0.5,
        0 , -0.0310466 , 0.5,
        0 , 0 , -0.5,
        0 , 0 , 0.5,
        0.301595 , 0 , -0.5,
        0.301595 , 0 , 0.5 };
    pointArray=pointArray_under;
    nbPoints=8;
    static int faceArray_under[]=
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
    faceArray=faceArray_under;
    nbFaces=12;
    advance=0.301595;
    }
    break;
