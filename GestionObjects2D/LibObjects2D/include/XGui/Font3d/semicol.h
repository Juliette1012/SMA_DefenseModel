  case ';':
    {
    static double pointArray_semicol[]=
      { 0.0541931 , 0.088705 , 0.5,
        0 , -0.042758 , 0.5,
        0.0363827 , -0.057658 , 0.5,
        0.115316 , 0.063341 , 0.5,
        0.0305961 , 0.319093 , 0.5,
        0.0305961 , 0.253016 , 0.5,
        0.0935902 , 0.253016 , 0.5,
        0.0935902 , 0.319093 , 0.5,
        0.0541931 , 0.088705 , -0.5,
        0.0363827 , -0.057658 , -0.5,
        0 , -0.042758 , -0.5,
        0.115316 , 0.063341 , -0.5,
        0.0305961 , 0.319093 , -0.5,
        0.0935902 , 0.253016 , -0.5,
        0.0305961 , 0.253016 , -0.5,
        0.0935902 , 0.319093 , -0.5 };
    pointArray=pointArray_semicol;
    nbPoints=16;
    static int faceArray_semicol[]=
      { 0 , 1 , 2,
        0 , 2 , 3,
        4 , 5 , 6,
        4 , 6 , 7,
        8 , 9 , 10,
        8 , 11 , 9,
        12 , 13 , 14,
        12 , 15 , 13,
        2 , 1 , 10,
        2 , 10 , 9,
        3 , 2 , 9,
        3 , 9 , 11,
        0 , 3 , 11,
        0 , 11 , 8,
        1 , 0 , 8,
        1 , 8 , 10,
        5 , 4 , 12,
        5 , 12 , 14,
        6 , 5 , 14,
        6 , 14 , 13,
        7 , 6 , 13,
        7 , 13 , 15,
        4 , 7 , 15,
        4 , 15 , 12 };
    faceArray=faceArray_semicol;
    nbFaces=24;
    advance=0.115316;
    }
    break;
