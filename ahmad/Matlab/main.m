%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all%
clc      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mat_eta = csvread('mat_eta.csv',1,0);
mat_p = csvread('m_p.csv',1,0);
mat_A = mat_eta;
mat_C = mat_eta;
h = 5; iteration = 1; k = 5; t = 1:size(mat_p);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
taux = taux_accroissement( mat_eta,mat_p);

alpha1 = coeff_depot1( mat_p,mat_eta);

alpha2 = coeff_depot2( mat_p,mat_eta);

alpha3 = coeff_depot3( mat_p,mat_eta);

alpha4 = coeff_depot4( mat_p,mat_eta);

alpha5 = coeff_depot5( mat_p,mat_eta);

coeff_envol = coeff_envol( 50, mat_eta, mat_eta);

N22 = calculN2(h,taux,coeff_envol);
N11 = calculN1(h,k,mat_p,alpha1,mat_eta);
for i =1:iteration
mat_C = calcul_C(h,mat_A,mat_C,alpha2,N11);
    
mat_A = calcul_A(h,mat_A,mat_C,coeff_envol,N22);
%figure,clf,spy (mat_A),title('dispersion ailees A')
%figure(1),clf, spy(mat_A),title('dispersion ailees A')

end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%figure(1),clf,plot (t,mat_C),title('dispersion apteres C')

 
%  figure(2),clf,spy (mat_C),title('dispersion apteres C')%,colormap hot;
% figure(2),clf,plot(mat_A),title('dispersion ailees A'),camlight right;
