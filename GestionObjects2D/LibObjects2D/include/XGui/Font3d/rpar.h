  case ')':
    {
    static double pointArray_rpar[]=
      { 0.0982676 , 0.496745 , 0.5,
        0 , 0.496745 , 0.5,
        0.0723495 , 0.378172 , 0.5,
        0.157797 , 0.378657 , 0.5,
        0.10201 , 0.212752 , 0.5,
        0.181844 , 0.212752 , 0.5,
        0.157519 , 0.046501 , 0.5,
        0.0724879 , 0.047679 , 0.5,
        0 , -0.070963 , 0.5,
        0.0982676 , -0.070963 , 0.5,
        0.0982676 , 0.496745 , -0.5,
        0.0723495 , 0.378172 , -0.5,
        0 , 0.496745 , -0.5,
        0.157797 , 0.378657 , -0.5,
        0.10201 , 0.212752 , -0.5,
        0.181844 , 0.212752 , -0.5,
        0.157519 , 0.046501 , -0.5,
        0.0724879 , 0.047679 , -0.5,
        0.0982676 , -0.070963 , -0.5,
        0 , -0.070963 , -0.5 };
    pointArray=pointArray_rpar;
    nbPoints=20;
    static int faceArray_rpar[]=
      { 0 , 1 , 2,
        0 , 2 , 3,
        3 , 2 , 4,
        3 , 4 , 5,
        6 , 5 , 4,
        6 , 4 , 7,
        7 , 8 , 9,
        7 , 9 , 6,
        10 , 11 , 12,
        10 , 13 , 11,
        13 , 14 , 11,
        13 , 15 , 14,
        16 , 14 , 15,
        16 , 17 , 14,
        17 , 18 , 19,
        17 , 16 , 18,
        1 , 0 , 10,
        1 , 10 , 12,
        2 , 1 , 12,
        2 , 12 , 11,
        4 , 2 , 11,
        4 , 11 , 14,
        7 , 4 , 14,
        7 , 14 , 17,
        8 , 7 , 17,
        8 , 17 , 19,
        9 , 8 , 19,
        9 , 19 , 18,
        6 , 9 , 18,
        6 , 18 , 16,
        5 , 6 , 16,
        5 , 16 , 15,
        3 , 5 , 15,
        3 , 15 , 13,
        0 , 3 , 13,
        0 , 13 , 10 };
    faceArray=faceArray_rpar;
    nbFaces=36;
    advance=0.181844;
    }
    break;
