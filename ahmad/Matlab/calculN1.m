function [matn] = calculN1(h,k,D,alpha1,vitesse)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    f = 1;

   for i=1:196
            for j=1:194
                

                alpha1ij(i,j)= ((1 + h + h*alpha1(i,j)) + (2 * h /(k*k) *D(i,j))) ;
                vec1(1,f) = alpha1ij(i,j);
                alpha2ij(i,j)  = ((-h/k)*(D(i,j)/k + vitesse(i,j)/2) ) ;
                vec2(1,f) = alpha2ij(i,j);
                alpha3ij(i,j)  = ((-h/k)*(D(i,j)/k - vitesse(i,j)/2) ) ;
                vec3(1,f) = alpha3ij(i,j);

            f = f +1;
            end
   end
%             for i=1:196*194
%           matn(i,1)  = vec2(1,i);
%           matn(i,2) =  vec1(1,i);
%           matn(i,3)  = vec3(1,i);
%             end

 matn = gallery('tridiag',vec2(1,1:38023),vec1(1,:),vec3(1,1:38023));
% Replace inv(A)*b with A\b and replace b*inv(A) with b/A.
end