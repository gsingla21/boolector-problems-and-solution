void demorgans_law()
{
    Btor *btor=boolector_new();
    boolector_set_opt(btor,BTOR_OPT_MODEL_GEN,1);
    BoolectorSort bsort8=boolector_bitvec_sort(btor,8);
    BoolectorNode *a=boolector_var(btor,bsort8,"a");
    BoolectorNode *b=boolector_var(btor,bsort8,"b");
    
    BoolectorNode *norab;
    norab=boolector_nor(btor,a,b);
    
    BoolectorNode *nota,*notb,*andab;
    nota=boolector_not(btor,a);
    notb=boolector_not(btor,b);
    andab=boolector_and(btor,nota,notb);

    BoolectorNode *u1=boolector_eq(btor,norab,andab);
    boolector_assert(btor,u1);

    BoolectorNode *nandab;
    nandab=boolector_nand(btor,a,b);

    BoolectorNode *orab;
    orab=boolector_or(btor,nota,notb);

    BoolectorNode *u2=boolector_eq(btor,nandab,orab);
    boolector_assert(btor,u2);
    
    int result=boolector_sat(btor);
    if(result==BOOLECTOR_SAT)
    cout<<"SAT"<<endl;
    else if(result==BOOLECTOR_UNSAT)
    cout<<"UNSAT"<<endl;
    else
    cout<<"OTHER"<<endl;
    
    if(result==BOOLECTOR_UNSAT)
    {
        boolector_release_all(btor);
        boolector_delete(btor);
        return;
    }

    //boolector_print_model(btor,"btor",stdout);

    boolector_release_all(btor);
    boolector_delete(btor);
    return;
}
