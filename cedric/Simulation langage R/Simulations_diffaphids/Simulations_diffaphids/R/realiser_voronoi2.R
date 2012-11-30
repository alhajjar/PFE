affect_val_test<-function(am2,am1){
A=am2
B=am1
na<-nrow(A)
nb<-nrow(B)
D2<-matrix(nrow=na,ncol=nb)

for (i in 1:nb){
D2[,i]<-(B[i,1]-A[,1])^2+(B[i,2]-A[,2])^2
}
D=apply(D2,1,which.min)
#renvoie l'indice de la colonne ou se trouve le min

D

}

#=================================================================================
realiser_voronoi2<-function(coord_villes,donnees){

coord_temp_connues<-donnees[,1:2]

am<-coord_villes

ind_toto<-affect_val_test(coord_villes,coord_temp_connues)

for(j in 3:dim(donnees)[2]){
	#print(c("j=",j))
	#toto<-c()
	toto<-donnees[ind_toto,j]
	am<-cbind(am,toto)
}
am

}
#===============================================================================

