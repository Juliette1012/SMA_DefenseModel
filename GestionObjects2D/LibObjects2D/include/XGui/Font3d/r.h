  case 'r':
    {
    static double pointArray_r[]=
      { 0 , 0 , 0.5,
        0.0680531 , 0 , 0.5,
        0.0680531 , 0.314901 , 0.5,
        0 , 0.314901 , 0.5,
        0.0680531 , 0.279835 , 0.5,
        0.0680531 , 0.190161 , 0.5,
        0.122177 , 0.252808 , 0.5,
        0.136868 , 0.323772 , 0.5,
        0.168538 , 0.314832 , 0.5,
        0.144075 , 0.245046 , 0.5,
        0 , 0 , -0.5,
        0.0680531 , 0.314901 , -0.5,
        0.0680531 , 0 , -0.5,
        0 , 0.314901 , -0.5,
        0.0680531 , 0.279835 , -0.5,
        0.122177 , 0.252808 , -0.5,
        0.0680531 , 0.190161 , -0.5,
        0.136868 , 0.323772 , -0.5,
        0.168538 , 0.314832 , -0.5,
        0.144075 , 0.245046 , -0.5 };
    pointArray=pointArray_r;
    nbPoints=20;
    static int faceArray_r[]=
      { 0 , 1 , 2,
        0 , 2 , 3,
        4 , 5 , 6,
        4 , 6 , 7,
        8 , 7 , 6,
        8 , 6 , 9,
        10 , 11 , 12,
        10 , 13 , 11,
        14 , 15 , 16,
        14 , 17 , 15,
        18 , 15 , 17,
        18 , 19 , 15,
        1 , 0 , 10,
        1 , 10 , 12,
        5 , 1 , 12,
        5 , 12 , 16,
        6 , 5 , 16,
        6 , 16 , 15,
        9 , 6 , 15,
        9 , 15 , 19,
        8 , 9 , 19,
        8 , 19 , 18,
        7 , 8 , 18,
        7 , 18 , 17,
        4 , 7 , 17,
        4 , 17 , 14,
        2 , 4 , 14,
        2 , 14 , 11,
        3 , 2 , 11,
        3 , 11 , 13,
        0 , 3 , 13,
        0 , 13 , 10 };
    faceArray=faceArray_r;
    nbFaces=32;
    advance=0.168538;
    }
    break;
