#!/bin/bash
echo "installation librairie PFE"
cd test
cp libpfe.a /usr/local/lib/
ldconfig /usr/local/lib
cd ../Includes
cp * /usr/include
echo "installation terminée pour compilé il suffit d'écrire  'g++ -o win main.cpp -lpfe' "
