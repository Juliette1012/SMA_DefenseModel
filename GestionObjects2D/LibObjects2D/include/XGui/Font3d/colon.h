  case ':':
    {
    static double pointArray_colon[]=
      { 0 , 0.0796262 , 0.5,
        0.0629594 , 0.013549 , 0.5,
        0.0629594 , 0.0796262 , 0.5,
        0 , 0.013549 , 0.5,
        0 , 0.319093 , 0.5,
        0.0629594 , 0.253016 , 0.5,
        0.0629594 , 0.319093 , 0.5,
        0 , 0.253016 , 0.5,
        0 , 0.0796262 , -0.5,
        0.0629594 , 0.0796262 , -0.5,
        0.0629594 , 0.013549 , -0.5,
        0 , 0.013549 , -0.5,
        0 , 0.319093 , -0.5,
        0.0629594 , 0.319093 , -0.5,
        0.0629594 , 0.253016 , -0.5,
        0 , 0.253016 , -0.5 };
    pointArray=pointArray_colon;
    nbPoints=16;
    static int faceArray_colon[]=
      { 0 , 1 , 2,
        0 , 3 , 1,
        4 , 5 , 6,
        4 , 7 , 5,
        8 , 9 , 10,
        8 , 10 , 11,
        12 , 13 , 14,
        12 , 14 , 15,
        3 , 0 , 8,
        3 , 8 , 11,
        1 , 3 , 11,
        1 , 11 , 10,
        2 , 1 , 10,
        2 , 10 , 9,
        0 , 2 , 9,
        0 , 9 , 8,
        7 , 4 , 12,
        7 , 12 , 15,
        5 , 7 , 15,
        5 , 15 , 14,
        6 , 5 , 14,
        6 , 14 , 13,
        4 , 6 , 13,
        4 , 13 , 12 };
    faceArray=faceArray_colon;
    nbFaces=24;
    advance=0.0629594;
    }
    break;
