// Autogenerated by nvert_protofile.py on 2015-05-06.
// Do not edit this file directly.
// The template for this file is located at:
// ../../../../../../../../templates/AstSubclass.java
package com.rethinkdb.ast.gen;

import com.rethinkdb.ast.helper.Arguments;
import com.rethinkdb.ast.helper.OptArgs;
import com.rethinkdb.ast.RqlAst;
import com.rethinkdb.proto.TermType;
import java.util.*;



public class Uuid extends RqlQuery {


    public Uuid(java.lang.Object arg) {
        this(new Arguments(arg), null);
    }
    public Uuid(Arguments args, OptArgs optargs) {
        this(null, args, optargs);
    }
    public Uuid(RqlAst prev, Arguments args, OptArgs optargs) {
        this(prev, TermType.UUID, args, optargs);
    }
    protected Uuid(RqlAst previous, TermType termType, Arguments args, OptArgs optargs){
        super(previous, termType, args, optargs);
    }

    public static Uuid fromArgs(Object... args){
        return new Uuid(new Arguments(args), null);
    }

}
