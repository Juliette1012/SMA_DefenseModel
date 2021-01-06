  case '\'':
    {
    static double pointArray_quote[]=
      { 0 , 0.314902 , 0.5,
        0 , 0.314902 , -0.5,
        0.05648 , 0.314902 , -0.5,
        0.05648 , 0.314902 , 0.5,
        0.161886 , 0.425782 , -0.5,
        0.161886 , 0.425782 , 0.5,
        0.0690928 , 0.425782 , -0.5,
        0.0690928 , 0.425782 , 0.5 };
    pointArray=pointArray_quote;
    nbPoints=8;
    static int faceArray_quote[]=
      { 0 , 1 , 2,
        3 , 0 , 2,
        3 , 2 , 4,
        5 , 3 , 4,
        5 , 4 , 6,
        7 , 5 , 6,
        7 , 6 , 1,
        0 , 7 , 1,
        5 , 7 , 0,
        1 , 6 , 4,
        3 , 5 , 0,
        1 , 4 , 2 };
    faceArray=faceArray_quote;
    nbFaces=12;
    advance=0.161886;
    }
    break;
