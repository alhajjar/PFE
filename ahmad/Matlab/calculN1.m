function [matn] = calculN1(h,k,D,alpha1,vitesse)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    f = 1;

   for i=1:196
            for j=1:194
                
                vec1(1,f)= ((1 - h + h*alpha1(i,j)) + (2 * h /(k*k) *D(i,j))) ;
                
                vec2(1,f)  = ((-h/k)*(D(i,j)/k + vitesse(i,j)/2) ) ;
                
                vec3(1,f)  = ((-h/k)*(D(i,j)/k - vitesse(i,j)/2) ) ;

            f = f +1;
            end
   end

 matn = gallery('tridiag',vec2(1,1:38023),vec1(1,:),vec3(1,1:38023));
% Replace inv(A)*b with A\b and replace b*inv(A) with b/A.
end