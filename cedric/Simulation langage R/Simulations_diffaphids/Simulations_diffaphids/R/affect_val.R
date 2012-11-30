affect_val1 <-function(mat,coord_ind,coord_villes){
A=coord_ind
B=coord_villes
na<-nrow(A)
nb<-nrow(B)
D2<-matrix(nrow=na,ncol=nb)

for (i in 1:nb){
D2[,i]<-(B[i,1]-A[,1])^2+(B[i,2]-A[,2])^2
}
D=apply(D2,1,which.min)
#renvoie l'indice de la colonne ou se trouve le min


mat2=mat
mat2[which(is.na(mat)==TRUE)]=mat[which(is.na(mat)==FALSE)[D]]


return(mat2)
}

#==============================================================================
affect_val <-
function(mat,coord_ind,coord_villes){
A=coord_ind
B=coord_villes
D2=matrix(0,nrow(A),1)
for (i in 1:nrow(B)){
C=matrix(0,nrow(A),2)
C[,1]=B[i,1]
C[,2]=B[i,2]
D=as.matrix((C[,1]-A[,1])^2+(C[,2]-A[,2])^2)
D2=cbind(D2,D)
}
D2=D2[,-1]
D=apply(D2,1,which.min)

mat2=mat
mat2[which(is.na(mat)==TRUE)]=mat[which(is.na(mat)==FALSE)[D]]

return(mat2)
}

