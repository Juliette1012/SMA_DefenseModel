  case 'y':
    {
    static double pointArray_y[]=
      { 0.13278 , -0.115316 , 0.5,
        0.332365 , 0.3149 , 0.5,
        0.25059 , 0.3149 , 0.5,
        0.0532923 , -0.115316 , 0.5,
        0.159975 , 0.116771 , 0.5,
        0.0805272 , 0.3149 , 0.5,
        0 , 0.3149 , 0.5,
        0.118365 , 0.023908 , 0.5,
        0.13278 , -0.115316 , -0.5,
        0.25059 , 0.3149 , -0.5,
        0.332365 , 0.3149 , -0.5,
        0.0532923 , -0.115316 , -0.5,
        0.159975 , 0.116771 , -0.5,
        0 , 0.3149 , -0.5,
        0.0805272 , 0.3149 , -0.5,
        0.118365 , 0.023908 , -0.5 };
    pointArray=pointArray_y;
    nbPoints=16;
    static int faceArray_y[]=
      { 0 , 1 , 2,
        0 , 2 , 3,
        4 , 5 , 6,
        4 , 6 , 7,
        8 , 9 , 10,
        8 , 11 , 9,
        12 , 13 , 14,
        12 , 15 , 13,
        0 , 3 , 11,
        0 , 11 , 8,
        1 , 0 , 8,
        1 , 8 , 10,
        2 , 1 , 10,
        2 , 10 , 9,
        4 , 2 , 9,
        4 , 9 , 12,
        5 , 4 , 12,
        5 , 12 , 14,
        6 , 5 , 14,
        6 , 14 , 13,
        7 , 6 , 13,
        7 , 13 , 15,
        3 , 7 , 15,
        3 , 15 , 11 };
    faceArray=faceArray_y;
    nbFaces=24;
    advance=0.332365;
    }
    break;
