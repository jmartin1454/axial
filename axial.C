// ROOT script to plot axial magnetic field due to current loops

TCanvas *vC1;  // This is important so as not to get crashes.

Int_t MAX=1000; // maximum number of inner or outer coils


// Globalize the coil parameters
Int_t ncoils;
Double_t *rinner;
Double_t *zinner;
Double_t *router;
Double_t *zouter;
Double_t iinner=4.087446e-01;  // from femm_helper.pl
Double_t iouter=-1.021862e-01;
//Double_t iinner=0.514327;  // from isolevels told by COMSOL
//Double_t iouter=-0.128445;
Double_t iinneronly=3.576516e-01;

// Globalize fundamental constants
Double_t pi=TMath::Pi();
Double_t mu0=4*pi*1e-7; // permeability of free space



Double_t b(Double_t z) {
  Double_t btot=0;
  Int_t i;
  for(i=0;i<ncoils;i++){
    //    cout << rinner[i] << " " << zinner[i] << endl;
    btot+=mu0/2*iinner*pow(rinner[i],2)/pow(pow(rinner[i],2)+pow(z-zinner[i],2),1.5);
    //    cout << router[i] << " " << zouter[i] << endl;
    btot+=mu0/2*iouter*pow(router[i],2)/pow(pow(router[i],2)+pow(z-zouter[i],2),1.5);
  }
  return btot;
} 


Double_t b_inneronly(Double_t z) {
  Double_t btot=0;
  Int_t i;
  for(i=0;i<ncoils;i++){
    btot+=mu0/2*iinneronly*pow(rinner[i],2)/pow(pow(rinner[i],2)+pow(z-zinner[i],2),1.5);
  }
  return btot;
}


void readcoils() {


  ifstream fin;
  Int_t i;

  // read in radii and z positions of inner coil
  fin.open("sphere-radii-and-z-inner.txt");
  i=0;
  while(fin>>rinner[i]>>zinner[i])i++;
  fin.close();

  // read in radii and z positions of outer coil
  fin.open("sphere-radii-and-z-outer.txt");
  i=0;
  while(fin>>router[i]>>zouter[i])i++;
  fin.close();
  ncoils=i;

}

Int_t axial() {

  vC1 = new TCanvas("vC1","square",200,10,700,700);

  rinner=new Double_t[MAX];
  zinner=new Double_t[MAX];
  router=new Double_t[MAX];
  zouter=new Double_t[MAX];

  readcoils();

  cout << b(0) << " " << b_inneronly(0) << endl;

  TF1 *fa3 = new TF1("fa3","b(x)",-10,10); 
  fa3->Draw();
  TF1 *fa4 = new TF1("fa3","b_inneronly(x)",-10,10); 
  fa4->SetLineColor(kBlue);
  fa4->Draw("same");

  cout << iinner/iouter << endl;

}
