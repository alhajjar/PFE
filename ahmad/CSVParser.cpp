////////////////////////////////////////////////////////////////////
//                                                                //
//                 -------------------------                      //
//                    CSVParser.cpp                               //
//                 -------------------------                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#include <CSVParser.hpp>

Matricedyn CSVParser(int m,int n, string filePath){

        Matricedyn mfinal(m,n);
mfinal = Matricedyn::Zero(m,n);
        Matricedyn mfin(m-1,n);
mfin = Matricedyn::Zero(m-1,n);
   // Matricedyn mfinal;
    string data(filePath);
    ifstream in(data.c_str());

    if (in.fail()){
        cout <<filePath <<" "<<"not found" <<endl;
    }

    else{

        vector< string > vec;
        vector<string> splitArray;
        vector<double> splitArrayd;
       // Matricedyn1 m ;
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

            for (int a=0;a!=nbcolonne;a++){
                try{
                    splitArrayd[a]= boost::lexical_cast<double>(splitArray[a]);
                    mfinal(nbligne,a)= splitArrayd.at(a);
                 }
                 catch(bad_lexical_cast &){
                    splitArrayd.push_back(0);
                   }
             }
          nbligne++;

          }
int k = n;
for (int i = 0;i<m-1;i++){
	for (int j = 0;j<n;j++){
mfin(i,j)=mfinal(i+1,j);

}

}
//cout<<mfinal.rows() <<"X" << mfinal.cols();

    }
 return mfin;
}

