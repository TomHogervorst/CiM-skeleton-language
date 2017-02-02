module types

imports

 src-gen/signatures/-

type rules
  
  Int(_): Integer()
  True(): Boolean()
  False(): Boolean()
  
  Array(Skeleton()): Skeleton()
  
  VarRef(r): ty
	where definition of r: ty
	
  BinOp(e1, binop, e2): rety
  where binop: (inty, rety)

  BinOp(e1, binop, e2):-
  where binop: (inty, rety)
  and e1: ety1
  and ety1 == inty
  else error $[This operator is not defined for an argument of type [ety1]] on e1 

  BinOp(e1, binop, e2):-
  where binop: (inty, rety)
  and e2: ety2
  and ety2 == inty
  else error $[This operator is not defined for an argument of type [ety2]] on e2
  
  Plus(): (Integer(), Integer())
  Minus(): (Integer(), Integer())
  Times(): (Integer(), Integer())
  DividedBy(): (Integer(), Integer())
  Modulo(): (Integer(), Integer())
  ToThePower(): (Integer(), Integer())
  GreaterThan(): (Integer(), Boolean())
  LessThan(): (Integer(), Boolean())
  EqualTo(): (Integer(), Boolean())
  And(): (Boolean(), Boolean())
  Or(): (Boolean(), Boolean())
  ConOp(op): (Array(Skeleton()), Skeleton())
  MaxOf(): (Integer(), Integer())
  
  Log2(exp): Integer()
 
  Log2(exp):-
  where exp : ty
  and ty == Integer()
  else error "Can only calculate the log2 of an integer value." on exp
  
  NOT(exp): Boolean()
  
  NOT(exp):-
  where
  exp : ty
  and ty == Boolean()
  else error "Not operator expects boolean input." on exp
  
  /*
  	Array type rules
  */
  
  ManualDefinition([elem|list*]): Array(ty)
  where elem : ty
  
  Append(exp1, exp2): Array(ty)
  where exp2: ty
    
  Append(exp1, exp2):-
  where exp1: ty1
  and exp2: ty2
  and (ty1 == ty2 or ty1 == Array(ty2) or ty2 == Array(ty1))
  else error "Can only merge arrays of the same type" on exp2
 
  Range(exp1, exp2): Array(Integer())
  
  Range(exp1, exp2):-
  where exp1 : ty
  and ty == Integer()
  else error "Can only create a range between two integer values." on exp1
  
  Range(exp1, exp2):-
  where exp2 : ty
  and ty == Integer()
  else error "Can only create a range between two integer values." on exp2
  
  Interval(exp1, exp2, exp3): Array(Integer()) 
  
  Interval(exp1, exp2, exp3):-
  where exp1 : ty
  and ty == Integer()
  else error "Can only create a range between two integer values." on exp1
  
  Interval(exp1, exp2, exp3):-
  where exp2 : ty
  and ty == Integer()
  else error "Can only create a range with an integer interval." on exp2
  
  Interval(exp1, exp2, exp3):-
  where exp3 : ty
  and ty == Integer()
  else error "Can only create a range between two integer values." on exp3
  
  Increment(exp1, exp2): Array(Integer())
  
  Increment(exp1, exp2):-
  where exp1 : ty
  and ty == Array(Integer())
  else error "Can only increment an array of integers." on exp1
  
  Increment(exp1, exp2):-
  where exp2 : ty
  and ty == Integer()
  else error "Can only increment an array by an integer value." on exp2
  
  ShiftRight(exp1, exp2): Array(ty)
  where exp1 : Array(ty)
  
  ShiftRight(exp1, exp2):-
  where exp2 : ty
  and ty == Integer()
  else error "Can only shift an array right by an integer." on exp2
  
  ShiftLeft(exp1, exp2): Array(ty)
  where exp1 : Array(ty)
  
  ShiftLeft(exp1, exp2):-
  where exp2 : ty
  and ty == Integer()
  else error "Can only shift an array left by an integer." on exp2
  
  PartOfArray(exp1, exp2): someType
  where exp1 : someType
  else error "Can only take a part of an array." on exp1
  
  PartOfArray(exp1, exp2):-
  where exp2 : ty
  and (ty == Integer() or ty == Array(Integer()))
  else error "Can only take from an array at (an array of) integer indices." on exp2
  
   /*
  	Skeleton typing rules
  */
  
  Nop(): Skeleton()
  
  LibModNum(num): Skeleton()
  
  Repeat(exp1, exp2): Array(ety2)
  where exp2: ety2
  
  Repeat(exp, skel):-
  where exp: ty
  and ty == Integer()
  else error "Integer expected here." on exp
  
  Connect(skel1, conop, skel2): Array(Skeleton())
  
  Connect(skel1, conop, skel2):-
  where skel1: ty
    and (ty == Array(Skeleton()) or ty == Skeleton())
  else error "Can only connect two (arrays of) skeletons." on skel1
  
  Connect(skel1, conop, skel2):-
  where skel2: ty
    and (ty == Array(Skeleton()) or ty == Skeleton())
  else error "Can only connect two (arrays of) skeletons." on skel2
  
  CompRef(entity, args*): ty
  where definition of entity: (ty, arg_ty*)

  CompRef(entity, args*):-
  where definition of entity: (ty, expected_ty*)
	and args*: args_ty*
	and (args_ty* == expected_ty*)
  else error $[Expected arguments of types [expected_ty*] instead of arguments of types [args_ty*]] on args*
  
  Map(name, exp1, exp2): Array(ety1)
  where exp1 : ety1
  
  Map(name, exp1, exp2):-
  where definition of name : ty
  and exp2 : ety2
  and ety2 == Array(ty)
  else error $[Cannot assign values of type [ety2] to variable of type [ty]] on exp2
  
  FoldRight(binop, exp): rety
   where binop: (inty, rety)
 
  FoldRight(binop, exp):-
  	where binop: (inty, rety)
  	and exp: ety
  	and ety == Array(inty)
  	else error $[Cannot fold a value of type [ety] when the operator expects type Array([inty]).] on exp
  	
  FoldLeft(binop, exp): rety
   where binop: (inty, rety)
 
  FoldLeft(binop, exp):-
  	where binop: (inty, rety)
  	and exp: ety
  	and ety == Array(inty)
  	else error $[Cannot fold a value of type [ety] when the operator expects type Array([inty]).] on exp
  
  /*
    Statement typing rules
  */
  
  VarAssign(v, e):-
  where e: ety
  	and definition of v: vty
  	and ety == vty
	else error $[Cannot assign a value of type [ety] to a variable of type [vty]] on e

  ArrayAssign(v, array, e):-
  where e:ety
  	and definition of v: Array(vty)
  	and ety == vty
  	else error $[Cannot assign a value of type [ety] to an array of type [vty]] on e
  
  ArrayAssign(v, array, e):-
  where array: ty
    and (ty == Array(Integer()) or ty == Integer())
  else error "Can only assign to (an array of) integer indices." on array

  SignalAssign(skel, _, _, exp):- 
  where exp: ty
 	and (ty == Array(Integer()) or ty == Integer())
  else error "An array must be used to define a part of a signal." on exp
 	
  OutputAssign(exp, _, _):-
  where exp: ty
 	and (ty == Array(Integer()) or ty == Integer())
  else error "An array must be used to define a part of a signal." on exp
 	
  IfThenElse(exp, _, _):-
  where exp: ty
 	and ty == Boolean()
  else error "The condition must be a boolean value." on exp
  
  WhileLoop(exp, _):-
  where exp: ty
    and ty == Boolean()
  else error "The condition must be a boolean value." on exp
  
  ForLoop(name, exp, _):-
  where definition of name: nty
  	and exp: ety
  	and ety == nty or ety == Array(nty)
  	else error $[Type of variable [name] doesn't match type [ety]] on name
   	
  CompAttrAssign(name, index, attr, exp):-
  where attr: aty
  	and exp: ety
  	and ety == ety
  	else error $[This attribute expects value of type [aty]] on exp
  	
  CompAttrAssign(name, index, attr, exp):-
  where index: ity
  	and ity == Integer()
  	else error $[The index has to be an integer number] on index
  
  SingleCompAttrAssign(name, attr, exp):-
  where attr: aty
  	and exp: ety
  	and ety == aty
  	else error $[This attribute expects value of type [aty]] on exp
  
  CompAttr(modRef, attr):rety
  where attr: rety
  
  Outport(_): Port()
  Inport(_): Port()
  Outports(): Port()
  Inports(): Port()
  GlobalOutport(_): Port()
  GlobalInport(_): Port()
  GlobalOutports(): Port()
  GlobalInports(): Port()
  OutportPos(_): Coordinate()
  OutportMir(_): Integer()
  OutportRot(_): Integer()
  InportPos(_): Coordinate()
  InportMir(_): Integer()
  InportRot(_): Integer()
  Position(): Coordinate()
  Size(): Coordinate()
  Delay(): Integer()
  Time(): Integer()
  Rotation(): Integer()
  Mirror(): Boolean()
  
  
  CoordX(exp): Integer()
  
  CoordX(exp):-
  where exp: ety
    and ety == Coordinate()
    else error "Can only take X element of a coordinate" on exp
    
  CoordY(exp): Integer()
  
  CoordY(exp):-
  where exp: ety
    and ety == Coordinate()
    else error "Can only take Y element of a coordinate" on exp
  
  CoordVal(exp1, exp2): Coordinate()
  
  CoordVal(exp1, exp2):-
  where exp1: ety1
  	and ety1 == Integer()
  	else error "Coordinate can only consist of two integers" on exp1
  	
  CoordVal(exp1, exp2):-
  where exp2: ety2
  	and ety2 == Integer()
  	else error "Coordinate can only consist of two integers" on exp2
  	
  CoordTranslate(coord, exp): Coordinate()
  
  CoordTranslate(coord, exp):-
  where exp: ety
  	and ety == Coordinate()
  	else error "Can only translate a coordinate by a coordinate value" on exp
  	
  CoordTranslate(coord, exp):-
  where coord: cty
  	and cty == Coordinate()
  	else error "Can only translate a coordinate" on coord
  	
  CoordRotate(coord, exp): Coordinate()
  
  CoordRotate(coord, exp):-
  where exp: ety
  	and ety == Integer()
  	else error "Can only rotate a coordinate by a integer value" on exp
  	
  CoordRotate(coord, exp):-
  where coord: cty
  	and cty == Coordinate()
  	else error "Can only rotate a coordinate" on coord
  
 /*
 	Declarations typing rules
 */
 
  ArgDecl(ty, arg): ty
  
  SigArg(_, exp):-
    where exp: ty
 	and ty == Integer()
  else error "The size of a signal should be a integer." on exp
  
  SignalDecl(_, exp):-
  where exp: ty
 	and ty == Integer()
  else error "A signal can only be defined with an integer size." on exp
 	
 /*
 	Signal typing rules
 */
  SigRef(_, exp):-
  where exp: ty
 	and (ty == Array(Integer()) or ty == Integer())
  else error "An array must be used to define a part of a signal." on exp
 	
  InputSig(exp):-
  where exp: ty
 	and (ty == Array(Integer()) or ty == Integer())
  else error "An array must be used to define a part of a signal." on exp
 	
  ConcurSigLoop(_, exp, _):-
  where exp: ty
  	and (ty == Array(Integer()) or ty == Integer())
  else error "Can only create a concurrent loop from an array." on exp