%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all%
clc      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mat_eta = csvread('mat_eta.csv',1,0);
mat_p = csvread('m_p.csv',1,0);

h = 5; iteration = 1; k = 5; t = 1:size(mat_p);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
taux = taux_accroissement( mat_eta,mat_eta);

alpha1 = coeff_depot1( mat_p,mat_eta);

alpha2 = coeff_depot2( mat_p,mat_eta);

alpha3 = coeff_depot3( mat_p,mat_eta);

alpha4 = coeff_depot4( mat_p,mat_eta);

alpha5 = coeff_depot5( mat_p,mat_eta);

coeff_envol = coeff_envol( 50, mat_eta, mat_eta);

N22 = calculN2(h,taux,alpha2);

mat_A = calcul_A(h,mat_p,mat_eta,alpha1,N22,iteration);

N11 = calculN1(h,k,mat_p,alpha1,mat_p);

mat_C = calcul_C(h,mat_p,mat_p,alpha2,N11,iteration);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1),clf,plot (t,mat_C),title('dispersion apteres C')
figure(2),clf,plot (t,mat_A),title('dispersion ailees A')
