
function [MATRICE_A] = calcul_A(h,MATRICE_A,MATRICE_C,coeffdepot1,N22)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 f = 1;
 
   for i=1:196
            for j=1:194
            vec(f,1) =   h* (coeffdepot1(i,j)* MATRICE_C(i,j)) + MATRICE_A(i,j); 
MATRICE_A(i,j) = N22(1,f)* vec(f,1);
            f = f +1;
            end
   end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
