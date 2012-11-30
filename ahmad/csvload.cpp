#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

int main()
{
    using namespace std;
    using namespace boost;

    string data("mat_eta.csv");

    ifstream in(data.c_str());
    if (!in.is_open()) return 1;

    typedef tokenizer< escaped_list_separator<char> > Tokenizer;
    vector< string > vec;
    vector<string> splitArray;
    vector< vector<string> > matrice;
    vector< string>::iterator iter_jj;
    vector< vector<string> >::iterator iter_ii;
    string line;

    while (getline(in,line))
    {
        Tokenizer tok(line);
        vec.assign(tok.begin(),tok.end());


        // vector now contains strings from one row, output to cout here
        //copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, "|"));
//cout<<vec.at(0);
  //  cout<<vec.size();
    split(splitArray, vec.at(0), is_any_of(";"));
 //for (unsigned int j = 0; j < splitArray.size(); ++j)
    // { // prints all the vector elements

          //cout << splitArray[2] ;
     //}
     //cout << vec.at(0)<<"\n----------------------" << endl;
     matrice.push_back(splitArray);
}
//cout << splitArray.at(0)<<splitArray.at(1);
/*// on efface la premiere ligne (les titres)//*/
    matrice.erase(matrice.begin());

for(iter_ii=matrice.begin(); iter_ii!=matrice.end(); iter_ii++)

   {

      for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end(); iter_jj++)

      {

         cout << *iter_jj<<"\t";

      }
cout << "\n----------------------" << endl;
   }

    }

