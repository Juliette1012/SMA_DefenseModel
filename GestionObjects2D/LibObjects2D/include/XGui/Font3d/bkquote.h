  case '`':
    {
    static double pointArray_bkquote[]=
      { 0.105406 , 0.314902 , -0.5,
        0.161886 , 0.314902 , -0.5,
        0.161886 , 0.314902 , 0.5,
        0.105406 , 0.314902 , 0.5,
        0 , 0.425782 , -0.5,
        0 , 0.425782 , 0.5,
        0.0927932 , 0.425782 , -0.5,
        0.0927932 , 0.425782 , 0.5 };
    pointArray=pointArray_bkquote;
    nbPoints=8;
    static int faceArray_bkquote[]=
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
    faceArray=faceArray_bkquote;
    nbFaces=12;
    advance=0.161886;
    }
    break;
