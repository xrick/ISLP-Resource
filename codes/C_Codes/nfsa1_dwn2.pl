/* NFSA1.PL	 A nondeterministic finite-state automaton to		*/
/*		 recognise English-like monosyllabic phoneme strings	*/

accept(String):- move(s1,String).

move(State,Symbol):-
	transition(State,Symbol,end).
move(StateA,[Symbol|Rest]):-
	transition(StateA,Symbol,StateB),
	move(StateB,Rest).

/* Enumerate all acceptable strings */

loop:- accept(A), write(A), nl, fail.	

transition(s1,s,s2).
transition(s1,p,s3).
transition(s1,t,s3).
transition(s1,k,s3).
transition(s1,b,s3).
transition(s1,d,s3).
transition(s1,g,s3).
transition(s1,f,s3).
transition(s1,'T',s3).
transition(s1,'S',s3).
transition(s1,p,s4).
transition(s1,t,s4).
transition(s1,k,s4).
transition(s1,b,s4).
transition(s1,d,s4).
transition(s1,g,s4).
transition(s1,f,s4).
transition(s1,v,s4).
transition(s1,s,s4).
transition(s1,'T',s4).
transition(s1,'D',s4).
transition(s1,'S',s4).
transition(s1,h,s4).
transition(s1,'C',s4).
transition(s1,'J',s4).
transition(s1,r,s4).
transition(s1,l,s4).
transition(s1,w,s4).
transition(s1,j,s4).
transition(s1,m,s4).
transition(s1,n,s4).
transition(s2,p,s3).
transition(s2,t,s3).
transition(s2,k,s3).
transition(s2,p,s4).
transition(s2,t,s4).
transition(s2,k,s4).
transition(s2,m,s4).
transition(s2,n,s4).
transition(s2,l,s4).
transition(s2,w,s4).
transition(s2,f,s4).
transition(s3,r,s4).
transition(s3,l,s4).
transition(s3,w,s4).
transition(s3,j,s6).
transition(s4,'I',s5).
transition(s4,e,s5).
transition(s4,a,s5).
transition(s4,o,s5).
transition(s4,'U',s5).
transition(s4,'@',s7).
transition(s4,a,s7).
transition(s4,'I',s8).
transition(s4,e,s8).
transition(s4,'&',s8).
transition(s4,'V',s8).
transition(s4,0,s8).
transition(s4,'U',s8).
transition(s4,3,s9).
transition(s4,'A',s9).
transition(s4,'O',s9).
transition(s4,u,s9).
transition(s4,i,s9).
transition(s4,'@',s9).
transition(s5,'@',s9).
transition(s5,'I',s9).
transition(s6,u,s9).
transition(s7,'U',s9).
transition(s8,l,s10).
transition(s8,m,s10).
transition(s8,n,s10).
transition(s8,'N',s10).
transition(s8,b,s11).
transition(s8,d,s11).
transition(s8,g,s11).
transition(s8,'D',s11).
transition(s8,v,s11).
transition(s8,l,s11).
transition(s8,b,s12).
transition(s8,'J',s12).
transition(s8,g,s12).
transition(s8,v,s12).
transition(s8,'D',s12).
transition(s8,z,s12).
transition(s8,p,s14).
transition(s8,t,s14).
transition(s8,k,s14).
transition(s8,f,s14).
transition(s8,d,s14).
transition(s8,l,s14).
transition(s8,n,s14).
transition(s8,'C',s15).
transition(s8,f,s15).
transition(s8,s,s15).
transition(s8,'S',s15).
transition(s8,'T',s16).
/* State 9 is an end state if there are no more letters left */
transition(s9,[],end).		
transition(s9,l,s10).
transition(s9,m,s10).
transition(s9,n,s10).
transition(s9,b,s11).
transition(s9,d,s11).
transition(s9,g,s11).
transition(s9,v,s11).
transition(s9,'D',s11).
transition(s9,l,s11).
transition(s9,b,s12).
transition(s9,'J',s12).
transition(s9,g,s12).
transition(s9,v,s12).
transition(s9,'D',s12).
transition(s9,z,s12).
transition(s9,'Z',s12).
transition(s9,p,s14).
transition(s9,t,s14).
transition(s9,k,s14).
transition(s9,f,s14).
transition(s9,m,s14).
transition(s9,p,s15).
transition(s9,k,s15).
transition(s9,f,s15).
transition(s9,'C',s15).
transition(s9,s,s15).
transition(s9,'S',s15).
transition(s9,'T',s16).
/* State 10 is an end state if there are no more letters left */
transition(s10,[],end).	
transition(s10,b,s11).
transition(s10,d,s11).
transition(s10,v,s11).
transition(s10,'J',s12).
transition(s10,v,s12).
transition(s10,z,s12).
transition(s10,p,s14).
transition(s10,t,s14).
transition(s10,k,s14).
transition(s10,f,s14).
transition(s10,p,s15).
transition(s10,k,s15).
transition(s10,'C',s15).
transition(s10,f,s15).
transition(s10,s,s15).
transition(s10,'S',s15).
/* State 11 is an end state if there are no more letters left */
transition(s11,[],end).	
transition(s11,z,s12).
/* State 12 is an end state if there are no more letters left */
transition(s12,[],end).	
transition(s12,d,s13).
/* State 13 is an end state if there are no more letters left */
transition(s13,[],end).	
/* State 14 is an end state if there are no more letters left */
transition(s14,[],end).	
transition(s14,s,s15).
transition(s14,'T',s16).
/* State 15 is an end state if there are no more letters left */
transition(s15,[],end).	
transition(s15,t,s16).
transition(s15,'T',s16).
/* State 16 is an end state if there are no more letters left */
transition(s16,[],end).	
transition(s16,s,s13).

