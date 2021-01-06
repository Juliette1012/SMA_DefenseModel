  case '|':
    {
    static double pointArray_pipe[]=
      { 0 , -0.079833 , -0.5,
        0.0443522 , -0.079833 , -0.5,
        0.0443522 , -0.079833 , 0.5,
        0 , -0.079833 , 0.5,
        0 , 0.505615 , -0.5,
        0 , 0.505615 , 0.5,
        0.0443522 , 0.505615 , -0.5,
        0.0443522 , 0.505615 , 0.5 };
    pointArray=pointArray_pipe;
    nbPoints=8;
    static int faceArray_pipe[]=
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
    faceArray=faceArray_pipe;
    nbFaces=12;
    advance=0.0443522;
    }
    break;
