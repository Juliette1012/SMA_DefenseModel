  case '"':
    {
    static double pointArray_dblquote[]=
      { 0.0153153 , 0.27942 , -0.5,
        0.0603607 , 0.27942 , -0.5,
        0.0603607 , 0.27942 , 0.5,
        0.0153153 , 0.27942 , 0.5,
        0 , 0.425782 , -0.5,
        0 , 0.425782 , 0.5,
        0.0753987 , 0.425782 , -0.5,
        0.0753987 , 0.425782 , 0.5,
        0.130631 , 0.27942 , -0.5,
        0.175746 , 0.27942 , -0.5,
        0.175746 , 0.27942 , 0.5,
        0.130631 , 0.27942 , 0.5,
        0.115316 , 0.425782 , -0.5,
        0.115316 , 0.425782 , 0.5,
        0.190714 , 0.425782 , -0.5,
        0.190714 , 0.425782 , 0.5 };
    pointArray=pointArray_dblquote;
    nbPoints=16;
    static int faceArray_dblquote[]=
      { 0 , 1 , 2,
        0 , 2 , 3,
        4 , 0 , 3,
        4 , 3 , 5,
        6 , 4 , 5,
        6 , 5 , 7,
        1 , 6 , 7,
        1 , 7 , 2,
        8 , 9 , 10,
        8 , 10 , 11,
        12 , 8 , 11,
        12 , 11 , 13,
        14 , 12 , 13,
        14 , 13 , 15,
        9 , 14 , 15,
        9 , 15 , 10,
        2 , 7 , 5,
        4 , 6 , 1,
        2 , 5 , 3,
        0 , 4 , 1,
        10 , 15 , 13,
        12 , 14 , 9,
        10 , 13 , 11,
        8 , 12 , 9 };
    faceArray=faceArray_dblquote;
    nbFaces=24;
    advance=0.190714;
    }
    break;
