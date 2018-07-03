[ ParserError error_type;
  switch( error_type )
  {
    STUCK_PE: return StuckError();
    UPTO_PE: return UpToError();
    NUMBER_PE: return NumberError();
    CANTSEE_PE: return CantSeeError();
    TOOLIT_PE: return TooLittleError();
    NOTHELD_PE: return NotHeldError();
!    MULTI_PE: return MultipleObjectsError();
    VAGUE_PE: return VagueError();
!    EXCEPT_PE: return ExclusionError();
!    ANIMA_PE: return AnimateError();
!    VERB_PE: return UnkownVerbError();
!    SCENERY_PE: return SceneryError();
!    ITGONE_PE: return ItGoneError();
!    JUNKAFTER_PE: return JunkAfterError();
    TOOFEW_PE: return TooFewError();
!    NOTHING_PE: return NothingError();
    default: rfalse;
  };
];

[ StuckError;
  switch( random(3) )
  {
    1: print_ret "~Sorry, didn't catch that. Please clarify.~";
    2: print_ret "~Er, what? Not sure what you meant by that.~";
    3: print_ret "~Didn't copy that. Uncertain how to proceed.~";
  }
];

[ UpToError;
  print_ret "~I understood the first part, but the rest...~";
];

[ NumberError;
  print_ret "~I need a number, and I'm pretty sure that wasn't a number.~";
];

[ CantSeeError;
  print "~Uhhhh... I don't see any '";
  PrintErroneousInput();
  print_ret "' anywhere.~";
];

[ TooLittleError;
  print_ret "~I think you need to tell me more.~";
];

[ NotHeldError;
  print_ret "~I'm not holding that at the moment.~";
];

[ VagueError;
  print_ret
    "~I'm not sure which you're referring to.";
];

[ TooFewError;
  print_ret "~I don't think I have enough to do that...~";
];

[ PrintErroneousInput wordnum word nwords stop pos end;
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
  }
];

! "You can't see any such thing."
