{
gROOT -> Reset();
TFile f("brachytherapy.root");
TCanvas* c1 = new TCanvas("c1", " ");
TH2F *h20 = (TH2F*)f.Get("h20");
h20->Draw("");					   
}
