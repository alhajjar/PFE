function [MATRICE_A] = calcul_A(h,MATRICE_C,MATRICE_A,coeffdepot1,N22,iteration)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for i=1:iteration
 MATRICE_A = h* (coeffdepot1*N22* MATRICE_C) + MATRICE_A;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%