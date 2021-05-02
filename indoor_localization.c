1.  void lettura_file(){
2.       FILE *f;
3.       FILE *fp;
4.       int i=0,j=0,t=0;
5.       float rssi1[MAX],rssi2[MAX],rssi3[MAX];
6.       float tempo[MAX],tempo2[MAX],tempo3[MAX];
7.       char namefile1[]="B1.txt";
8.       char namefile2[]="B2.txt";
9.       char namefile3[]="B3.txt";
10.      float x[MAX],y[MAX];
11.      float u=6.0; // DISTANZA BEACON 1- BEACON 2
12.      float v=6.0; // DISTANZA BEACON 1-BEACON 3
13.      float distanza1[MAX],distanza2[MAX],distanza3[MAX];
14.      int cont=0;
15.      //Apertura del file
16.      f=fopen(namefile1,"r");
17.      while(!feof(f)){
18.          fscanf(f,"%f",&rssi1[i]);
19.          fscanf(f,"%f",&distanza1[i]);
20.          fscanf(f,"%f",&tempo[i]);
21.    //printf("%f\t%f\t%f\n",rssi1[i],distanza[i],tempo[i]);
22.             i++;
23.             cont++;
24.           }fclose(f);
25.         f=fopen(namefile2,"r");
26.                while(!feof(f)){
27.                  fscanf(f,"%f",&rssi2[j]);
28.                  fscanf(f,"%f",&distanza2[j]);
29.                  fscanf(f,"%f",&tempo2[j]);
30.             //printf("%f\t%f\t%f\n",rssi2[j],distanza2[j],tempo2[j]);
31.             j++;
32.             }fclose(f);
33.             f=fopen(namefile3,"r");
34.                    while(!feof(f)){
35.                          fscanf(f,"%f",&rssi3[t]);
36.                          fscanf(f,"%f",&distanza3[t]);
37.                          fscanf(f,"%f",&tempo3[t]);
38.           //printf("%f\t%f\t%f\n",rssi3[t],distanza3[t],tempo3[t]);
39.                                 t++;
40.                           }fclose(f);
41.                     for(i=0;i<cont;i++){
42.              x[i]=(pow(u,2)+ (pow(distanza1[i]/100,2)-pow(distanza2[i]/100,2)))/(2*u);
43.              y[i]=(pow(v,2)+ (pow(distanza1[i]/100,2)-pow(distanza3[i]/100,2)))/(2*v);
44.                     }
45.                     fp=fopen("coordinate.txt","w");
46.                     if(fp==NULL)
47.                     {
48.                         perror("Errore di apertura del file\n");
49.                     }
50.                     else
51.                     {
52.                         printf("File coordinate.txt creato correttamente\n");
53.                         for(i=0;i<cont;i++){
54.                             if(x[i]>0 && y[i]>0){
55.                             fprintf(fp,"%f  ",x[i]);
56.                             fprintf(fp,"%f\n",y[i]);
57.                                 }
58.                         }
59.                         fclose(fp);
60.                     }
61.       }
62.  
63. int main(){
64.     lettura_file();
65.     system("pause");
66.     return 0;
67. }
