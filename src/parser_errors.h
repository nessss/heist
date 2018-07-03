[ ParserError error_type;
  switch( error_type )
  {
    case STUCK_PE: return StuckError();
!    case UPTO_PE: return UpToError();
!    case NUMBER_PE: return NumberError();
!    case CANTSEE_PE: return CantSeeError();
!    case TOOLIT_PE: return TooLittleError();
!    case NOTHELD_PE: return NotHeldError();
!    case MULTI_PE: return MultipleObjectsError();
!    case VAGUE_PE: return VagueError();
!    case EXCEPT_PE: return ExclusionError();
!    case ANIMA_PE: return AnimateError();
!    case VERB_PE: return UnkownVerbError();
!    case SCENERY_PE: return SceneryError();
!    case ITGONE_PE: return ItGoneError();
!    case JUNKAFTER_PE: return JunkAfterError();
!    case TOOFEW_PE: return TooFewError();
!    case NOTHING_PE: return NothingError();
    default: rfalse;
  }
];

[ StuckError;
  switch( random(3) )
  {
    case 1: print_ret "~Sorry, didn't catch that. Please clarify.~";
    case 2: print_ret "~Er, what? Not sure what you meant by that.~";
    case 3: print_ret "~Didn't copy that. Uncertain how to proceed.~";
  }
];

![ UpToError;
!]

[ CantSeeError  wordnum word nwords stop pos end;
  wordnum=saved_oops;
#ifdef TARGET_GLULX;
  nwords=parse-->0;
#ifnot;
  nwords=parse->1;
#endif;
  
  if( wordnum > 0 )
  {
#ifdef TARGET_GLULX;
    word=parse-->(wordnum*3-2);
#ifnot;
    word=parse-->(wordnum*2-1);
#endif;
    if( word && ( word->#dict_par1 & $80) ~= $80 ) rfalse;

    print "~Uhhhh... I don't see any '";
    do
    {
      pos=WordAddress(wordnum); end = Wordlength(wordnum) + pos;
      for( : pos<end: pos++ ) print (char) pos->0;
      wordnum++;
      if( wordnum > nwords ) stop = 1;
      else
      {
#ifdef TARGET_GLULX;
        word=parse-->(wordnum*3-2);
#ifnot;
        word=parse-->(wordnum*2-1);
#endif;
        if( word )
        {
          if( word->#dict_par1 & $88 ~= $80) stop=1;
          if( word == AND1__WD or ',//' or './/' or BUT1__WD or BUT2__WD ) stop = 1;
        }
      }
      if( ~~stop ) print "' '";
    } until ( stop );
    oops_from = saved_oops;
    print_ret "' anywhere.~";
  }
];

! "You can't see any such thing."
