////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    CSVParser.cpp                               //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "CSVParser.hpp"

Matrice CSVParser(const string filePath){

    Matrice mfinal= Matrice::Zero();
    string data(filePath);
    ifstream in(data.c_str());

    if (in.fail()){
        cout <<filePath <<" "<<"not found" <<endl;
    }

    else{

        vector< string > vec;
        vector<string> splitArray;
        vector<float> splitArrayd;
        Matrice1 m ;
        string line;
        int nbligne=0;
        /* ************************************************************* */
        while (getline(in,line))
        {
            Tokenizer tok(line);
            vec.assign(tok.begin(),tok.end());
        /*// decomposition du vecteur obtenu et on le met dans un autre vecteur//*/
            split(splitArray, vec.at(0), is_any_of(";"));
            int nbcolonne=splitArray.size();

            for (int a=0;a<nbcolonne;a++){
                try{
                    splitArrayd[a]= boost::lexical_cast<float>(splitArray[a]);
                    m(nbligne,a)= splitArrayd.at(a);
                 }
                 catch(bad_lexical_cast &){
                    splitArrayd.push_back(0);
                   }
             }
          nbligne++;

          }
    /*// delete first row//*/
    mfinal=m.block<196,194>(1,0);
    }
 return mfinal;
}

