  case 'E':
    {
    static double pointArray_E[]=
      { 0 , 0 , 0.5,
        0.230631 , 0 , 0.5,
        0.230631 , 0.079834 , 0.5,
        0.0798339 , 0.079834 , 0.5,
        0.0798339 , 0.190715 , 0.5,
        0.226196 , 0.190715 , 0.5,
        0.226196 , 0.270549 , 0.5,
        0.0798339 , 0.270549 , 0.5,
        0.0798339 , 0.345948 , 0.5,
        0.230631 , 0.345948 , 0.5,
        0.230631 , 0.425782 , 0.5,
        0 , 0.425782 , 0.5,
        0 , 0 , -0.5,
        0.230631 , 0.079834 , -0.5,
        0.230631 , 0 , -0.5,
        0.0798339 , 0.079834 , -0.5,
        0.0798339 , 0.190715 , -0.5,
        0.226196 , 0.270549 , -0.5,
        0.226196 , 0.190715 , -0.5,
        0.0798339 , 0.270549 , -0.5,
        0.0798339 , 0.345948 , -0.5,
        0.230631 , 0.425782 , -0.5,
        0.230631 , 0.345948 , -0.5,
        0 , 0.425782 , -0.5 };
    pointArray=pointArray_E;
    nbPoints=24;
    static int faceArray_E[]=
      { 0 , 1 , 2,
        0 , 2 , 3,
        4 , 5 , 6,
        4 , 6 , 7,
        8 , 9 , 10,
        8 , 10 , 11,
        3 , 8 , 11,
        3 , 11 , 0,
        12 , 13 , 14,
        12 , 15 , 13,
        16 , 17 , 18,
        16 , 19 , 17,
        20 , 21 , 22,
        20 , 23 , 21,
        15 , 23 , 20,
        15 , 12 , 23,
        1 , 0 , 12,
        1 , 12 , 14,
        2 , 1 , 14,
        2 , 14 , 13,
        3 , 2 , 13,
        3 , 13 , 15,
        4 , 3 , 15,
        4 , 15 , 16,
        5 , 4 , 16,
        5 , 16 , 18,
        6 , 5 , 18,
        6 , 18 , 17,
        7 , 6 , 17,
        7 , 17 , 19,
        8 , 7 , 19,
        8 , 19 , 20,
        9 , 8 , 20,
        9 , 20 , 22,
        10 , 9 , 22,
        10 , 22 , 21,
        11 , 10 , 21,
        11 , 21 , 23,
        0 , 11 , 23,
        0 , 23 , 12 };
    faceArray=faceArray_E;
    nbFaces=40;
    advance=0.230631;
    }
    break;
