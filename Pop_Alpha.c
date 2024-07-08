//--------------------------------------------------------ILHAM DEKHISSI
//--------------------------------------------------------------------------Last Modified 18/06/2024
//-----------------------------------------------------------------------------------------For the excited states of the alpha--------------------------------------------------------------

#ifdef __CLING__
#pragma cling optimize(0)
#endif

#include <iostream>
#include <TMath.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TColor.h>
#include <vector>
#include <TLine.h>
#include <TGraph.h>
#include <sys/stat.h> //for mkdir
#include <sys/types.h>
#include <TLatex.h>

#include <TF1.h>
#include <TStyle.h>
#include "Riostream.h"
#include "TFile.h"
#include "TPad.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TF2.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "TAxis.h"
#include "TH1.h"
#include "TArrayD.h"
#include "TArrow.h"
#include "TLatex.h"


#include "Math/MinimizerOptions.h"
 


//___________________________Call of  the functions from the Functions.C------------------------------------


//.L Population_Alpha.c
//General_Pop()



//---------------Legends for the canvas------------------------------------

TLegend *legend = new TLegend(0.2, 0.9, 0.4, 0.7); 
TLegend *legend2 = new TLegend(0.2, 0.9, 0.4, 0.7);

//--------------Threshold of the dexcitation of the channels----------------

double threshold[2] = {19.81 , 23.85};



//-----------------The root File to store the canvas----------------------------------------------------


TFile* outputfile = new TFile("Output_alpha_1.root", "RECREATE");


//_____________________________________This is the begining of the main function___________________________________________

void Signal_Alpha(int Proj, char *SProj , int Target , char *STarget, int energy , int Proj2, char *SProj2 , int Target2 , char *STarget2, int energy2 , int bin) {
    

      gStyle->SetOptFit(kTRUE);
   
    
    
    TString Files_names[4] = {Form("/scratch/dekhissi/Alpha/FilesRoot/CorrelationAnalysis%d%s%d%s%d_dd.root", Proj , SProj, Target, STarget, energy), Form("/scratch/dekhissi/Alpha/FilesRoot/CorrelationAnalysis%d%s%d%s%d_pt.root", Proj , SProj, Target, STarget, energy), Form("/scratch/dekhissi/Alpha/FilesRoot/CorrelationAnalysis%d%s%d%s%d_dd.root", Proj2 , SProj2, Target2, STarget2, energy2), Form("/scratch/dekhissi/Alpha/FilesRoot/CorrelationAnalysis%d%s%d%s%d_pt.root", Proj2 , SProj2, Target2, STarget2, energy2)}; 
  
	
   
   TH1::SetDefaultSumw2();   
      
//------------------------------------- This part sets for the name of each file that correspponds to each system  ------------------------------------
             
   TFile *file1_dd = TFile::Open(Files_names[0]); //files with dd
   TFile *file1_pt = TFile::Open(Files_names[1]); //files with pt
   
             
   TFile *file2_dd = TFile::Open(Files_names[2]); //files with dd
   TFile *file2_pt = TFile::Open(Files_names[3]); //files with pt
  
  

//--------------------------------Getting the files that correspond to each bin noted as i & each system/file noted as b-----------------------------------------------

 outputfile->cd(); //Go to the Root file
 
 
 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%THE ARROWS & THE TEXTS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 

//-----------This for the arrows of the thresholds of each channel-----------------
  
	//Threshold p - t  
  
 TArrow *ar_198 = new TArrow( 19.81 , 0.9 , 19.81 , 0.6 , 0.07 , "|>");
   ar_198->SetLineColor(4) ;
   ar_198->SetFillColor(4) ;
   ar_198->SetLineWidth(1) ;
   ar_198->SetLineStyle(1) ;
   
 TLatex *text_198 = new TLatex( 19.4 , 0.5, "#color[4]{E_{thr}(p-t) = 19.81 Mev}");
   text_198->SetTextSize(0.05);
   
   
      	//Threshold n - He
	
   TArrow *ar_205 = new TArrow( 20.58 , 0.9 , 20.58 , 0.6 , 0.07 , "|>");
   ar_205->SetLineColor(4) ;
   ar_205->SetFillColor(4) ;
   ar_205->SetLineWidth(1) ;
   ar_205->SetLineStyle(1) ;
   
 TLatex *text_205 = new TLatex( 20.62 , 0.7, "#color[4]{E_{thr}(n-He) = 20.58 Mev}");
   text_205->SetTextSize(0.05);
   
   	//Threshold d - d 
  
 TArrow *ar_238 = new TArrow( 23.85 , 0.55 , 23.85 , 0.9 , 0.07 , "|>");
   ar_238->SetLineColor(4) ;
   ar_238->SetFillColor(4) ;
   ar_238->SetLineWidth(1) ;
   ar_238->SetLineStyle(1) ;
   
 TLatex *text_238 = new TLatex( 23.89 , 0.6 , "#color[4]{E_{thr}(d-d) = 23.85 Mev}");
   text_238->SetTextSize(0.05);
   

  //-----------THIS IS FOR THE ARROW OF THE EXCITED STATE E = 20.21 MEV---------------
  
  

 TArrow *ar_20 = new TArrow( 20.21 , 1.2 , 20.21 , 1.0 , 0.07 , "|>");
   ar_20->SetLineColor(1) ;
   ar_20->SetFillColor(1) ;
   ar_20->SetLineWidth(1) ;
   ar_20->SetLineStyle(1) ;
   
 TLatex *text_20 = new TLatex(20.0, 1.21, "#color[1]{20.21 Mev (#Gamma = 0.5 Mev & J^{#Pi} = 0^{+})}");
   text_20->SetTextSize(0.05);

  
  //-----------THIS IS FOR THE ARROW OF THE EXCITED STATE E = 24.250 MEV--------------- 

 TArrow *ar_24 = new TArrow( 24.250 , 1.2 , 24.250 , 0.9 , 0.07 , "|>");
   ar_24->SetLineColor(1) ;
   ar_24->SetFillColor(1) ;
   ar_24->SetLineWidth(1) ;
   ar_24->SetLineStyle(1) ;
   
 TLatex *text_24 = new TLatex(22.8, 1.21, "#color[1]{24.25 Mev (#Gamma = 6.2 Mev & J^{#Pi} = 1^{-})}");
   text_24->SetTextSize(0.05);
     
     
//-----------THIS IS FOR THE ARROW OF THE EXCITED STATE E = 25.280 MEV--------------- 

 TArrow *ar_252 = new TArrow( 25.280 , 1.8 , 25.280 , 1.0 , 0.07 , "|>");
   ar_252->SetLineColor(1) ;
   ar_252->SetFillColor(1) ;
   ar_252->SetLineWidth(1) ;
   ar_252->SetLineStyle(1) ;
   
 TLatex *text_252 = new TLatex(25.0, 1.81, "#color[1]{25.28 Mev (#Gamma = 7.97 Mev & J^{#Pi} = 0^{-})}");
   text_252->SetTextSize(0.05);
   
   
      
//-----------THIS IS FOR THE ARROW OF THE EXCITED STATE E = 25.950 MEV--------------- 

 TArrow *ar_259 = new TArrow( 25.950 , 1.5 , 25.950 , 1.0 , 0.07 , "|>");
   ar_259->SetLineColor(1) ;
   ar_259->SetFillColor(1) ;
   ar_259->SetLineWidth(1) ;
   ar_259->SetLineStyle(1) ;
   
 TLatex *text_259 = new TLatex(25.76, 1.51, "#color[1]{25.95 Mev (#Gamma = 12.66 Mev & J^{#Pi} = 1^{-})}");
   text_259->SetTextSize(0.05);
   
   
         
//-----------THIS IS FOR THE ARROW OF THE EXCITED STATE E = 27.420 MEV--------------- 

 TArrow *ar_27 = new TArrow( 27.42 , 1.2 , 27.42 , 1.0 , 0.07 , "|>");
   ar_27->SetLineColor(1) ;
   ar_27->SetFillColor(1) ;
   ar_27->SetLineWidth(1) ;
   ar_27->SetLineStyle(1) ;
   
 TLatex *text_27 = new TLatex(27.20, 1.21, "#color[1]{27.420 Mev (#Gamma = 8.69 Mev & J^{#Pi} = 2^{+})}");
   text_27->SetTextSize(0.05);
   
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%THE HISTOGRAMS%%%%%%%%%%%%%%%%%%%%%%%%%%%%          
      
	 
 	TString histName = Form("h_cor_Ex_bin_%d",bin); //Call correlated spectrum for each bin of each file
	
            TH1F* hCorrel1_dd = (TH1F*)file1_dd->Get(histName);
	    TH1F* hCorrel1_pt = (TH1F*)file1_pt->Get(histName);
	    
	    TH1F* hCorrel2_dd = (TH1F*)file2_dd->Get(histName);
	    TH1F* hCorrel2_pt = (TH1F*)file2_pt->Get(histName);
	    
	    
	    hCorrel1_dd->Sumw2();
	    hCorrel2_dd->Sumw2();
	    
	    hCorrel1_pt->Sumw2();
	    hCorrel2_pt->Sumw2();
	    
	   
            histName = Form("h_uncor_Ex_bin_%d",bin); //Call uncorrelated spectrum for each bin of each file
	     
            TH1F* hUncor1_dd = (TH1F*)file1_dd->Get(histName);
	    TH1F* hUncor1_pt = (TH1F*)file1_pt->Get(histName);
	    
	    TH1F* hUncor2_dd = (TH1F*)file2_dd->Get(histName);
	    TH1F* hUncor2_pt = (TH1F*)file2_pt->Get(histName);
	     
	    hUncor1_dd->Sumw2();
	    hUncor2_dd->Sumw2();
	    
	    hUncor1_pt->Sumw2();
	    hUncor2_pt->Sumw2();
    
            double scaleFactor1_dd = hCorrel1_dd->Integral(200, 350) / hUncor1_dd->Integral(200, 350); // Scale for the normalization of the uncorrelated spectrum 200,350
	    hUncor1_dd->Scale(scaleFactor1_dd);
	    
	    double scaleFactor1_pt = hCorrel1_pt->Integral(200, 350) / hUncor1_pt->Integral(200, 350); // Scale for the normalization of the uncorrelated spectrum 200,350
	    hUncor1_pt->Scale(scaleFactor1_pt);
	    
	    double scaleFactor2_dd = hCorrel2_dd->Integral(200, 350) / hUncor2_dd->Integral(200, 350); // Scale for the normalization of the uncorrelated spectrum 200,350
	    hUncor2_dd->Scale(scaleFactor2_dd);
	    
	    double scaleFactor2_pt = hCorrel2_pt->Integral(200, 350) / hUncor2_pt->Integral(200, 350); // Scale for the normalization of the uncorrelated spectrum 200,350
	    hUncor2_pt->Scale(scaleFactor2_pt);



//---------------------------------Canvas of the Correlation Function shifted--------------------------------------------------

 TCanvas *c_fraction_shifted = new TCanvas(Form("Ratio_%d_%d%s%d%s_%d_%d%s%d%s_%d", bin, Proj, SProj  , Target , STarget , energy, Proj, SProj2  , Target2 , STarget2 , energy2), "Correlation Function shifted using the thresholds", 1200, 600);
 
 c_fraction_shifted->Divide(1,2);	

 //---------------------------CORRELATION FUNCTION as the Ratio-------------------------------------------
 

        TH1F* hfraction1_dd = (TH1F*)hCorrel1_dd->Clone(Form("h_1fraction_Bin_%d_Sys_%d%d_at_%d_dd", bin, Proj , Target, energy)); //Call each bin and each system
	TH1F* hfraction1_pt = (TH1F*)hCorrel1_pt->Clone(Form("h_1fraction_Bin_%d_Sys_%d%d_at_%d_pt", bin, Proj , Target, energy));
	
	
        TH1F* hfraction2_dd = (TH1F*)hCorrel2_dd->Clone(Form("h_2fraction_Bin_%d_Sys_%d%d_at_%d_dd", bin, Proj2 , Target2, energy2)); //Call each bin and each system
	TH1F* hfraction2_pt = (TH1F*)hCorrel2_pt->Clone(Form("h_2fraction_Bin_%d_Sys_%d%d_at_%d_pt", bin, Proj2 , Target2, energy2));
	
	
	hfraction1_dd->Sumw2();
	hfraction1_pt->Sumw2();
	
	hfraction2_dd->Sumw2();
	hfraction2_pt->Sumw2();
	
	
	hfraction1_dd->Divide(hCorrel1_dd, hUncor1_dd);
	hfraction1_pt->Divide(hCorrel1_pt, hUncor1_pt);
	
	hfraction2_dd->Divide(hCorrel2_dd, hUncor2_dd);
	hfraction2_pt->Divide(hCorrel2_pt, hUncor2_pt);
	
	
	
//------------------------------Fitting the background------------------------------------------------------------
	
		
    int bins = hfraction1_dd->GetNbinsX();
    
    int binmax = hfraction1_dd->GetXaxis()->GetXmax();
    
    int binmin = hfraction1_dd->GetXaxis()->GetXmin();

	
//--------------------------CORRELATION FUNCTION shifted - Threshold-------------------------------------------
 
 
   
 TH1F  *Corr_threshold1_dd = new TH1F(Form("Corr_Function_%d_Sys_%d%d_at_%d_dd", bin, Proj , Target , energy ), Form("The Correlation Functions of the d-d  & p-t channels for the systems {}^{%d}%s + {}^{%d}%s at %d Mev/A", Proj , SProj, Target , STarget , energy ), bins , binmin , binmax);
 
 
  TH1F  *Corr_threshold1_pt = new TH1F(Form("Corr_Function_%d_Sys_%d%d_at_%d_pt", bin, Proj , Target , energy ), Form("The Correlation Functions of the d-d  & p-t channels for the systems {}^{%d}%s + {}^{%d}%s at %d Mev/A", Proj , SProj, Target , STarget , energy ), bins , binmin , binmax);
  
  TH1F  *Corr_threshold2_dd = new TH1F(Form("Corr_Function_2_%d_Sys_%d%d_at_%d_dd", bin, Proj2 , Target2 , energy2 ), Form("The Correlation Functions of the d-d  & p-t channels for the systems {}^{%d}%s + {}^{%d}%s at %d Mev/A", Proj2 , SProj2, Target2 , STarget2 , energy2 ), bins , binmin , binmax);
 
  TH1F  *Corr_threshold2_pt = new TH1F(Form("Corr_Function_2_%d_Sys_%d%d_at_%d_pt", bin, Proj2 , Target2 , energy2 ), Form("The Correlation Functions of the d-d  & p-t channels for the systems {}^{%d}%s + {}^{%d}%s at %d Mev/A", Proj2 , SProj2, Target2 , STarget2 , energy2 ), bins , binmin , binmax);

  
  Corr_threshold1_dd->Sumw2();
  Corr_threshold1_pt->Sumw2();
  
  Corr_threshold2_dd->Sumw2();
  Corr_threshold2_pt->Sumw2();
  
  
 //------------The setting of the threshold-------------------
 
  for (int n = 1 ; n <= bins ; n++){
    
    double binContent1_dd = hfraction1_dd->GetBinContent(n);
    double binError1_dd = hfraction1_dd->GetBinError(n); 
    
    double binContent2_dd = hfraction2_dd->GetBinContent(n);
    double binError2_dd = hfraction2_dd->GetBinError(n); 
    
    
    double binContent1_pt = hfraction1_pt->GetBinContent(n);
    double binError1_pt = hfraction1_pt->GetBinError(n);
    
    double binContent2_pt = hfraction2_pt->GetBinContent(n);
    double binError2_pt = hfraction2_pt->GetBinError(n);
    
    
  //----------------Alpha-> d + d-------------------  
    
  Corr_threshold1_dd->SetBinContent( n , binContent1_dd);
  Corr_threshold1_dd->SetBinError(n, binError1_dd );
  Corr_threshold1_dd->GetXaxis()->SetRangeUser(19, 30);
  
    
  Corr_threshold2_dd->SetBinContent( n , binContent2_dd);
  Corr_threshold2_dd->SetBinError(n, binError2_dd );
  
   
   //---------------Alpha-> p + 3H--------------------
   
  Corr_threshold1_pt->SetBinContent( n , binContent1_pt);//Without the shift
  Corr_threshold1_pt->SetBinError(n, binError1_pt );
  Corr_threshold1_pt->GetXaxis()->SetRangeUser(19, 30);
  
   
  Corr_threshold2_pt->SetBinContent( n , binContent2_pt);//Without the shift
  Corr_threshold2_pt->SetBinError(n, binError2_pt );
  
    
}
  
  //------------------------------------The first Pad
  


   Corr_threshold1_dd->SetMarkerSize(1.2);
   Corr_threshold1_dd->SetMarkerColor(kRed);
   Corr_threshold1_dd->SetLineColor(kRed);
   Corr_threshold1_dd->SetMarkerStyle(24);
   legend->AddEntry(Corr_threshold1_dd, "Channel d-d" , "elp");
   Corr_threshold1_dd->SetStats(0);
   
   Corr_threshold1_pt->SetMarkerSize(1.2);
   Corr_threshold1_pt->SetMarkerColor(kBlack);
   Corr_threshold1_pt->SetLineColor(kBlack);
   Corr_threshold1_pt->SetMarkerStyle(20);
   legend->AddEntry(Corr_threshold1_pt, "Channel p-t" , "elp");
   Corr_threshold1_pt->SetStats(0);
   
   
  //-----The Y axis (Title / Labels / Range)-------------
  
  Corr_threshold1_pt->GetYaxis()->SetRangeUser(0.3, 2.0);
  
  Corr_threshold1_pt->GetYaxis()->SetTitleFont(62);
  
  Corr_threshold1_pt->GetYaxis()->SetNdivisions(602,kFALSE);
  

  Corr_threshold1_pt->GetYaxis()->SetTitle("1 + R(E_{x})");
  
  
  Corr_threshold1_pt->GetYaxis()->SetTitleSize(0.08);
  Corr_threshold1_pt->GetYaxis()->SetTitleOffset(0.58);
  
  Corr_threshold1_pt->GetYaxis()->SetLabelSize(0.07);
  Corr_threshold1_pt->GetYaxis()->SetLabelOffset(0.005);
  
  
  //-----The X axis (Title / Labels / Range)-------------
  
 
  
  Corr_threshold1_pt->GetXaxis()->SetTitle("E_{x} (Mev)");
  Corr_threshold1_pt->GetXaxis()->SetTitleFont(62);
  Corr_threshold1_pt->GetXaxis()->SetTitleSize(0.07);
  Corr_threshold1_pt->GetXaxis()->SetTitleOffset(0.62);
  
  
  Corr_threshold1_pt->GetXaxis()->SetLabelSize(0.07);
  Corr_threshold1_pt->GetXaxis()->SetLabelOffset(-0.006);
  
 

Corr_threshold1_pt->GetXaxis()->SetRangeUser(19.2, 30);



 
 
 //------------------------------------The Second Pad
 
 //------Markers------------
 
   Corr_threshold2_dd->SetMarkerSize(1.2);
   Corr_threshold2_dd->SetMarkerColor(kRed);
   Corr_threshold2_dd->SetLineColor(kRed);
   Corr_threshold2_dd->SetMarkerStyle(24);
   legend2->AddEntry(Corr_threshold2_dd, "Channel -dd" , "elp");
   Corr_threshold2_dd->SetStats(0);
 
   
   
  Corr_threshold2_pt->SetMarkerSize(1.2);
  Corr_threshold2_pt->SetMarkerColor(kBlack);
  Corr_threshold2_pt->SetLineColor(kBlack);
  Corr_threshold2_pt->SetMarkerStyle(20);
  legend2->AddEntry(Corr_threshold2_pt, "Channel p-t" , "elp");
  Corr_threshold2_pt->SetStats(0);
  
     
  //-----The Y axis (Title / Labels / Range)-------------
  
  Corr_threshold2_pt->GetYaxis()->SetRangeUser(0.3, 2.0);
  Corr_threshold2_pt->GetYaxis()->SetNdivisions(602,kFALSE);
  

  Corr_threshold2_pt->GetYaxis()->SetTitle("1 + R(E_{x})");
  Corr_threshold2_pt->GetYaxis()->SetTitleFont(62);
  
  
  Corr_threshold2_pt->GetYaxis()->SetTitleSize(0.08);
  Corr_threshold2_pt->GetYaxis()->SetTitleOffset(0.58);
  
  Corr_threshold2_pt->GetYaxis()->SetLabelSize(0.07);
  Corr_threshold2_pt->GetYaxis()->SetLabelOffset(0.005);
  
  Corr_threshold2_pt->GetXaxis()->SetRangeUser(19.2, 30);
  
  
  //-----The X axis (Title / Labels / Range)-------------
  
 
  
  Corr_threshold2_pt->GetXaxis()->SetTitle("E_{x} (Mev)");
  Corr_threshold2_pt->GetXaxis()->SetTitleFont(62);
  Corr_threshold2_pt->GetXaxis()->SetTitleSize(0.07);
  Corr_threshold2_pt->GetXaxis()->SetTitleOffset(0.62);
  
  
  Corr_threshold2_pt->GetXaxis()->SetLabelSize(0.07);
  Corr_threshold2_pt->GetXaxis()->SetLabelOffset(-0.006);
  
 

   //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%First Pad
  
c_fraction_shifted->cd(1);





Corr_threshold1_pt->Draw("P");
Corr_threshold1_dd->Draw("P same");

legend->Draw("same");

//--%%%%%%%%%%Threshold---

ar_198->Draw("same");
ar_238->Draw("same");
ar_205->Draw("same");

text_198->Draw("same");
text_238->Draw("same");
text_205->Draw("same");


//%%%%%%%%%%%Excited states-------

ar_20->Draw("same");
ar_24->Draw("same");
ar_252->Draw("same");
ar_259->Draw("same");
ar_27->Draw("same");

text_20->Draw("same");
text_24->Draw("same");
text_252->Draw("same");
text_259->Draw("same");
text_27->Draw("same");



 //----%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Second Pad
 
c_fraction_shifted->cd(2);

//--%%%%%%histograms--

Corr_threshold2_pt->Draw("P");
Corr_threshold2_dd->Draw("P same");

//legend2->Draw("same");

//--%%%%%%%%%%Threshold---

ar_198->Draw("same");
ar_238->Draw("same");
ar_205->Draw("same");

text_198->Draw("same");
text_238->Draw("same");
text_205->Draw("same");


//%%%%%%%%%%%Excited states-------

ar_20->Draw("same");
ar_24->Draw("same");
ar_252->Draw("same");
ar_259->Draw("same");
ar_27->Draw("same");

text_20->Draw("same");
text_24->Draw("same");
text_252->Draw("same");
text_259->Draw("same");
text_27->Draw("same");


    c_fraction_shifted->Modified();
    c_fraction_shifted->Update();
    
    
    
    TString title_Corr = Form("/scratch/dekhissi/Alpha/finalResults/%d%d_%d_%d%d_%d.pdf", Proj, Target , energy , Proj2, Target2 , energy2);
    c_fraction_shifted->SaveAs(title_Corr); 

  
 c_fraction_shifted->Write();


  
outputfile->Close();  


}// To close the void General_Pop()
