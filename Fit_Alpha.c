//--------------------------------------------------------ILHAM DEKHISSI
//--------------------------------------------------------------------------Last Modified 5/07/2024
//-----------------------------------------------------------------------------------------For 4He 

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
#include <iomanip>

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
#include "TTree.h"
#include <TList.h>

#include "Math/MinimizerOptions.h"
 


 


//___________________________Call of  the functions from the Functions.C------------------------------------


//.L Functions.C++
//.L Populations_32_AllCent.C
 

extern Double_t FondexpoN_A(Double_t *,Double_t *); //This is for the Nayak background 
extern Double_t CombinedFit_A(Double_t *,Double_t *); //Combined Fit
extern Double_t BreitWeigner_A(Double_t *,Double_t *); //This is for the first peak





/////____________This part will serve as vectors for the plots of the populations in terms of the centrality & system_____________________________
///
    
//For the plots of the populations ___Numbers of centralities & Names of the systems & Vectors to store the normalized Populations

 

    std::vector<int> histNumbers;
    std::vector<std::string> systems_names = {"64Ni64Ni", "58Ni64Ni", "64Ni58Ni", "64Ni64Ni"}; //names used for the each pdf & root Files 
    std::vector<std::string> systems_names_P = {"{64}^Ni + {64}^Ni", "{58}^Ni + {64}^Ni", "{64}^Ni +  {58}^Ni", "{64}^Ni + {64}^Ni"}; //names used for the Titles & Legends 
    
    TString histNumber[8] = {"1", "2", "3","4", "5", "6", "7","10"};
  
  
    
    std::vector<std::vector<double>> FinalPopulations1; //For the plot function
    std::vector<std::vector<double>> FinalPopulations2;
    
    std::vector<double> finalPopulations1;//where I store the populations
    std::vector<double> finalPopulations2; //vectors for the normalized populations
    std::vector<std::string> system_names;
     
    std::vector<double> finalErrors1; //for the errors
    std::vector<double> finalErrors2;
     
  //-----------------Initialization of the arrays------------------  
     


    Double_t fpop1systeme[4][9]; //for the plots of the first population in terms of the systems & centralities
    Double_t fpop2systeme[4][9]; //for the plots of the second population in terms of the systems & centralities 

    Double_t errors1systeme[4][9]; //For teh calculation of the errors on the populations
    Double_t errors2systeme[4][9];
    


    Double_t fTemperature[4][9]; //for the compuattaion of each Tempertaure for eavh system & centrality as the ratio of the two popoulations
  
 
    

//---For the plots of the populations in terms of the centrality & systems----------

//---------Initialization of the histograms

TH1F* histo1_system[9]; // I need 8 histograms to be plotted for the first population in terms of the systems for all centralities since the 8 is not plotted
TH1F* histo1_centrality[4];  // I need 4 histograms to be plotted for the first population in terms of the centrality for all systems

TH1F* histo2_system[9]; // I need 8 histograms to be plotted for the second population in terms of the systems for all centralities
TH1F* histo2_centrality[4]; // I need 4 histograms to be plotted for the second population in terms of the centrality for all systems

TH1F* histoT_system[9]; // For the temperatures in terms of the systems
TH1F* histoT_centrality[4];

TH1F* histoBe_system[4];
TH1F* histoC_system[4];
TH1F* histoC_N[4];
TH1F* histoHe_system[4];
TH1F* histo6He_system[4];
TH1F* histo_Mult[4];
TH1F* Mult_total_bin[4];



//---------------Vectors for teh figures Colors & Styles for the markers -------------------------------

std::vector<int> markerstyles = {20, 21, 26, 24, 23, 20, 20, 21, 22, 120};

std::vector<int> colors = {kRed, kBlue, kViolet, kBlack, kMagenta, kGreen, kBlack, kViolet};



//---------------Legends for the canvas------------------------------------

TLegend *legend1 = new TLegend(0.8 , 0.6 ,0.9 , 0.89); //histo of systems
TLegend *legend2 = new TLegend(0.1 , 0.7 , 0.48 , 0.9); // histo of centrality
TLegend *legendT = new TLegend(0.1 , 0.7 , 0.48 , 0.9); //For the temperatures
TLegend *legendT2 = new TLegend(0.1 , 0.7 , 0.48 , 0.9); //For the temperatures
TLegend *legendBe = new TLegend(0.4 , 0.6 ,0.89 , 0.89);
TLegend *legendC = new TLegend(0.4 , 0.6 ,0.89 , 0.89);
TLegend *legendHe = new TLegend(0.4 , 0.6 ,0.89 , 0.89);
TLegend *legend6He = new TLegend(0.4 , 0.6 ,0.89 , 0.89);



//----------------The line to check If the Corr Funct goes to 1----------------

TLine *line = new TLine(7,1,35,1);


//-----------------The root File to store the canvas----------------------------------------------------


TFile* outputfile = new TFile("/scratch/dekhissi/Alpha/Output_Alpha_Fit.root", "RECREATE");


//-----------------The Openeing of the 4 root files---------------------------------------------------------
    
    TString Files_names[1] = {"/scratch/dekhissi/Alpha/FilesRoot/CorrelationAnalysis64Ni64Ni52_pt.root"}; //6464 @ 52 Mev/A


//_____________________________________This part contains all the calculation & fit General_Pop___________________________________________

void Population_Alpha() {
    
 TList list;
 TList list2;
  
   TF1* fitFunction;
   TF1* fitFunction1;
   TF1* fitFunction2;
   TF1* fitFunction3;
   TF1* combinedFit;
   TF1* first_peak;
   TF1* second_peak;
   TF1* third_peak;
   TF1* Combinedback_diff;
   TF1* backN_fun;
    

//_________________Initialization of the Fitting functions____________________________________

    
  
   
    gStyle->SetOptFit(kTRUE);
     
    
   
    for (int system = 0; system < 1; system++){
    
       TFile *file = TFile::Open(Files_names[system]);  
       
       
        const char* systems_names_char = systems_names[system].data();  
       
    	for (int bin = 0 ;  bin < 8 ; bin++) {
	
	 int binNumber = atoi(histNumber[bin].Data());
	
   
//--------------------------------------------------Definition of the Nayak Background function for the fit--------------------------------------------
       
       	 fitFunction = (TF1*)gROOT->FindObject(Form("fitFunction_Bin_%d_Sys_%s", binNumber, systems_names_char));
         if(!fitFunction){
             fitFunction= new TF1(Form("fitFunction_Bin_%d_Sys_%s", binNumber, systems_names_char) , FondexpoN_A , 19.8 , 24 ,2);
            list.Add(fitFunction);
	    }
	    
	    double size = list.GetSize();
	    cout<<"size" <<size<<endl;
	    
	    cout<<"The function is : "<<Form("fitFunction_Bin_%d_Sys_%s", binNumber, systems_names_char)<<endl;

//--------------------------------------------------Definition of the First Peak function for the fit--------------------------------------------	    
         
       	 fitFunction1 = (TF1*)gROOT->FindObject(Form("fitFunction1_Bin_%d_Sys_%s", binNumber, systems_names_char));
         if(!fitFunction1){
             fitFunction1 = new TF1(Form("fitFunction1_Bin_%d_Sys_%s", binNumber, systems_names_char) , "gaus" , 19.9  , 20.4);
            list.Add(fitFunction1);
         }
	 
//--------------------------------------------------Definition of the CombinedFit function for the fit--------------------------------------------	 
	 
	 combinedFit = (TF1*)gROOT->FindObject(Form("combinedFit_Bin_%d_Sys_%s", binNumber, systems_names_char));
         if(!combinedFit){
             combinedFit = new TF1(Form("combinedFit_Bin_%d_Sys_%s", binNumber, systems_names_char) , CombinedFit_A, 19.8  , 24 , 4);
            list.Add(combinedFit);
         }
	 
	 	 
//-------------------------------------Definition of the First Peak X Uncorrelated function for the fit--------------------------------------------	    
            
   
  	 first_peak = (TF1*)gROOT->FindObject(Form("first_peak_Bin_%d_Sys_%s", binNumber, systems_names_char));
         if(!first_peak){
             first_peak = new TF1(Form("first_peak_Bin_%d_Sys_%s", binNumber, systems_names_char) , BreitWeigner_A , 19.8  , 20.4 , 2);
            list2.Add(first_peak);
         }


	 
	  
	  
  }//Closure for the system
  }//Closure for the bins
   
   
 TH1::SetDefaultSumw2(kTRUE); 

//------------------------------------------------------------%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Begining of the Computation%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%-------------------------------------------------    
  
    	//______________The loop on the system ---------- 
    
    for (int system = 0; system < 1; ++system){ //This is to call the three the files

         
      
//------------------------------------- This part sets for the name of each file that correspponds to each system / This part has to be optimized into a loop potentially ------------------------------------
             
   TFile *file = TFile::Open(Files_names[system]); 
   
        
   const char* systems_names_char = systems_names[system].data(); //This because the title of the pdf needs a character  for the acces to the TString 
        
   const char* systems_names_P_char = systems_names_P[system].data(); //This is for the titles & Legends


//--------------------------------Getting the files that correspond to each bin noted as i & each system/file noted as b-----------------------------------------------


   
    
   
         
      //______________The loop on the centrality----------  
	 
 	for (int bin = 0 ;  bin < 8 ; ++bin) {
	
	    TString histName = "h_cor_Ex_bin_" + histNumber[bin]; //Call correlated spectrum for each bin of each file
            TH1F* hCorrel = (TH1F*)file->Get(histName);
	    

            histName = "h_uncor_Ex_bin_" + histNumber[bin];
            TH1F* hUncorrel = (TH1F*)file->Get(histName);
	    
    
            double scaleFactor = hCorrel->Integral(200, 350) / hUncorrel->Integral(200, 350); // Scale for the normùalization of the uncorrelated spectrum 200,350
	    hUncorrel->Scale(scaleFactor);
	    
	   
            
            int binNumber = atoi(histNumber[bin].Data()); 
	    
	    
	    
	    TTree* chain = (TTree *)file->Get("check_tree");
	    
	    TH1F* h_p = new TH1F(Form("h_p_Sys_%s_at 32", systems_names_char) , Form("h_p_Bin_Sys_%s_at 32",  systems_names_char), 100 , 0 ,100);
	    TH1F* h_t = new TH1F(Form("h_t_Sys_%s_at 32", systems_names_char) , Form("h_t_Bin_Sys_%s_at 32",  systems_names_char), 100 , 0 ,100);
	    
	    chain->Draw("mtot_EC>>h_p", "z==1 && a==1 && theta<12");
	    chain->Draw("mtot_EC>>h_t", "z==1 && a==2 && theta<12");
	    
	    
            
           
	  //---------------Go TO THE OUTPUT FILE---------------------
    
 
 outputfile->cd(); //Go to the Root file	
	
	    

	
 //---------------------------CORRELATION FUNCTION as the Fraction-------------------------------------------

        TH1F* h_1fraction = (TH1F*)hCorrel->Clone(Form("h_1fraction_Bin_%d_Sys_%s_at32", binNumber, systems_names_char)); //Call each bin and each system
	
	
    h_1fraction->Divide(hCorrel, hUncorrel);
    TString Title_fraction = Form("The correlation function as the ratio of the correlated & uncorrelated for the system %s with a centrality %s at 32 Mev/A", systems_names_P_char, histNumber[bin].Data());
    h_1fraction->SetTitle(Title_fraction);
    h_1fraction->GetYaxis()->SetRangeUser(0, 2);
    h_1fraction->GetYaxis()->SetTitle("1+R(Ex)");
    h_1fraction->GetXaxis()->SetTitle("Ex(Mev)");
    h_1fraction->GetXaxis()->SetRangeUser(17, 25);
    h_1fraction->SetMarkerStyle(20);
    h_1fraction->SetMarkerSize(1.0);
    h_1fraction->SetMarkerColor(kBlue);
    

    h_1fraction->SetStats(0);
    
   

//-------------------------CANVAS-------------------------------------------------

        TCanvas *c1 = new TCanvas(Form("c1_Bin_%d_Sys_%s_at32", binNumber, systems_names_char), "(Un)/Correlated & Ratio & Difference", 1200, 600);
	
   // c1->Divide(1, 3);
    
    c1->cd(); //For the plot sof the fraction & diffrence
    
    h_1fraction->Draw();
    
//--------------------------FIT DE NAYAK---------------------------------------------

cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%This is for the BACKGROUND for the system" << " " <<systems_names_P_char<< " at the centrality "<<" "<<binNumber<<": "<<endl;

        
       	 fitFunction = (TF1*)list.FindObject(Form("fitFunction_Bin_%d_Sys_%s", binNumber, systems_names_char));
	 
  
   
	
    fitFunction->SetParName(0, "amplitude");
    fitFunction->SetParameter(0, 1.2); //Fix
    
    fitFunction->SetParName(1, "delta");
    fitFunction->SetParameter(1, 0.3); //Fix
    //fitFunction->Write();
    
    h_1fraction->Fit(Form("fitFunction_Bin_%d_Sys_%s", binNumber, systems_names_char), "R");
    
    //fitFunction->SetLineColor(kMagenta);
    //fitFunction->Draw(" L SAME ");

 

   
//----------------------------FIRST PEAK---------------------------------------------

cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%This is for the FIRST PEAK AT 20.2 for the system" << " " <<systems_names_P_char<< " at the centrality "<<" "<<binNumber<<": "<<endl;

        
       	 fitFunction1 = (TF1*)list.FindObject(Form("fitFunction1_Bin_%d_Sys_%s", binNumber, systems_names_char));
        
    
    fitFunction1->SetParName(0, "Amp_1");
    fitFunction1->SetParameter(0, 1.06472);
    
    fitFunction1->SetParName(1, "Mean_1");
    fitFunction1->FixParameter(1, 2.01673e+01 );
    
    fitFunction1->SetParName(2, "Sigma_1");
    fitFunction1->FixParameter(2,  9.36024e-01 );
    
    //fitFunction1->SetParLimits(1, 1.0 , 5.0);
    
    
    h_1fraction->Fit(Form("fitFunction1_Bin_%d_Sys_%s", binNumber, systems_names_char), "R");

    fitFunction1->SetLineColor(kBlack);
    fitFunction1->Draw(" L same");




//----------------------------FIRST COMBINED FIT---------------------------------------------

 ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000); // This is the solution for the call limit  
 
 cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%This is for the COMBINED FIT for the system" << " " <<systems_names_P_char<< " at the centrality "<<" "<<binNumber<<": "<<endl;
 
 

	 combinedFit =(TF1*)list.FindObject(Form("combinedFit_Bin_%d_Sys_%s", binNumber, systems_names_char));
        
	
	
	//------------Parameters Names-------------
     
    combinedFit->SetParName(0, Form("Amplitude_Bin %s_ Sys%s", histNumber[bin].Data(),systems_names_char));
    combinedFit->SetParName(1, Form("Delta_Bin %s_Sys %s", histNumber[bin].Data(),systems_names_char));
    
    combinedFit->SetParName(2, Form("Population_1_Bin %s_Sys %s", histNumber[bin].Data(),systems_names_char));
    combinedFit->SetParName(3, Form("Gamma_1_Bin %s_Sys %s", histNumber[bin].Data(),systems_names_char));
     
    	//------------Parameters Limit-------------

   // combinedFit->SetParLimits(2, 0, 20); //Population_1
   // combinedFit->SetParLimits(3, 0.1, 1);//gamma_1 0.2


  
      //------------Parameters Setting-------------

    combinedFit->SetParameter(0, 1.0);
    combinedFit->SetParameter(1, 0.85);
    
    combinedFit->FixParameter(2, fitFunction1->GetParameter(0));
    combinedFit->FixParameter(3, fitFunction1->GetParameter(1));
    combinedFit->FixParameter(4, fitFunction1->GetParameter(2));
    
   
    h_1fraction->Fit(Form("combinedFit_Bin_%d_Sys_%s", binNumber, systems_names_char), "R");
    
    
    combinedFit->SetLineColor(kGreen);
    combinedFit->SetLineWidth(2);
    combinedFit->Draw("same");
    
    
    
//----------------------------SECOND COMBINED WITH THE RELEASE---------------------------------------------
    
 cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%This is for the COMBINED FIT With the RELEASE OF THE BACKGROUND for the system" << " " <<systems_names_P_char<< " at the centrality "<<" "<<binNumber<<": "<<endl; 
     
    combinedFit->ReleaseParameter(2); 
    combinedFit->ReleaseParameter(3);
    combinedFit->ReleaseParameter(4);
    
    combinedFit->SetParameter(2, fitFunction1->GetParameter(0));
    combinedFit->SetParameter(3, fitFunction1->GetParameter(1));
    combinedFit->SetParameter(4, fitFunction1->GetParameter(2));
    
   
    
    //combinedFit->SetParLimits(1, 0, 5);
    
    h_1fraction->Fit(Form("combinedFit_Bin_%d_Sys_%s", binNumber, systems_names_char), "0S");
    
    h_1fraction->Draw(" P same");
    
    /*combinedFit->SetLineColor(kRed);
    combinedFit->SetLineWidth(2);
    combinedFit->Draw("same");*/
    
    c1->Write();
    
    //combinedFit->Write();

 
		//-----------------The Parameters found in the fit process----------------------

    double Population_1_new0 = combinedFit->GetParameter(2);
    double Gamma_1_new0 = combinedFit->GetParameter(3);
    
    
//-----------------------------THE DIFFRENCE DEFINITION WITH THE PEAKS------------------------------------------

////////////////-------------------------------------------first peak


    
 	//--------------The function describing the first peak defined using the parameters found in the CombinedFit (first_peak)-----------------------------------------
	   
        
first_peak = (TF1*)list2.FindObject(Form("first_peak_Bin_%d_Sys_%s", binNumber, systems_names_char));	

	
     first_peak->SetParameters(Population_1_new0, Gamma_1_new0);
     
     
     	//--------------The histogram describing the first peak X Uncorrelated spectrum (peak1_diff)-----------------------------------------
	
        TH1F *peak1_diff = new TH1F(Form("peak1_diff_Bin_%d_Sys_%s", binNumber, systems_names_char), Form("peak1_diff_Bin_%d_Sys_%s", binNumber, systems_names_char), hUncorrel->GetNbinsX(),  hUncorrel->GetXaxis()->GetXmin(),  hUncorrel->GetXaxis()->GetXmax());
     	
     
//the multiplication calculation of the functions defined with the combinedFit parameters for the first level & the uncorrelated spectrum
     
     
       for (int j = 0; j <= hUncorrel->GetNbinsX(); ++j) {
       
       double bin_center = hUncorrel->GetBinCenter(j);
       double value1 = first_peak->Eval(bin_center);//This is the value of the function at the bin center
       double result1 = value1 * hUncorrel->GetBinContent(j);
       peak1_diff->SetBinContent(j, result1);
       
       
    }
      

    
///////////////////------------------------------------------Combined Fit for the the diffrence spectrum


	//--------------The function describing the CombinedFit (Combinedback_diff)-----------------------------------------
 
    
//----------------------------------------------------------Important : Final Values of the populations ------------------------------------------------------------------------


//--------------I used this part to compare between the new population where the background is supposed to be extracted & teh correlated area where the background is still included for the tenth bin where all the particles are taken into account


        //%%%%%%%%%%%%%%%%%%%%%%%---------------------The counts of multiplicity of C12 ______________________________
        
        
        double A = h_p->GetBinContent(binNumber * 10 + 1);  
        h_p->Sumw2(); 
	
	double B = h_t->GetBinContent(binNumber * 10 + 1);  
        h_t->Sumw2(); 
	
	double N =  A + B;
	
	

	//--------First Peak Population Value--------

    double population_1 = peak1_diff->Integral(198,204); //Without the Background
    double population_normalized_1 = (100 * population_1)/N ;
    
    
	//-------Computation of the ERROR on the First Peak---------
 
    double population_1_error = peak1_diff->Integral(200,220); // The second interval
    
    double pop_mean_1 = (population_1_error + population_1)/2; // Mean value of the integrals
    
    double delta_pop_1 = (population_1_error - population_1)/2;  // This represents the Delta on the integral values 
    
    double error_N = h_p->GetBinError(binNumber * 10 + 1) + h_t->GetBinError(binNumber * 10 + 1); 
    
    double error_1 = sqrt((delta_pop_1 * delta_pop_1)/(pop_mean_1 * pop_mean_1) + (error_N * error_N)/ ( N * N ) ) * population_normalized_1 ; // The error on the normalized population 
  
  
  	//-----------Checking--------------------
	
//____The Normalized population 1 values for each bin and system  with the errors
cout<<"The Normalized Population of the first level With the error  "<<population_normalized_1<<endl;

            //cout<<"The Normalized Population of the first level With the error  "<<std::setprecision(4)<<population_normalized_1<<"+-"<<std::setprecision(4) <<error_1<<endl;
	
 //__Comparing the population found with the population found on the correlated spectrum
    
    
    double integral1_h1 = hCorrel->Integral(198,204); //With the background & directly on teh correlated spectrum 
    double h1_normalized_1  =  integral1_h1 ;
     
    cout<<"The number of counts of the correlated spectrum  "<<integral1_h1<<endl;
 
   cout<<"The Normalized h1 of the first level  "<<h1_normalized_1<<endl;
 

//___Plots of the spectra of the difference correlated & uncorrelated with the functions fiiting the peaks & the correlated spectrum
 

    TString title_Corr = Form("/scratch/dekhissi/Alpha/Spectra/The difference spectrum for the system %s and the centrality %d.pdf ", systems_names_char, binNumber);
    c1->SaveAs(title_Corr); //This will save the figures
    
    	    
       
		
   

//______________________Clear the Canvas ---------------------------------------------------------

        
  delete c1; 
    
    
//-------------------------This part stores the information of the populations & centrality & systems--------------------

   //---------Thesse variables are defined in order to use the Plot_Final_Populations_bin defined in the begining of the code
   
    //system_names.push_back(systems_name_char);
        
    //histNumbers.push_back(std::atoi(histNumber[bin].Data())); //I found atoi to convert the string to an integer
    
    
    
    finalPopulations1.push_back(population_normalized_1); // These are the vectors definded at the begining of the file
    
 //   finalErrors1.push_back(error_1);
   
 
 //---------Thesse variables are defined in order to use the Histograms defined afterwards
    
    fpop1systeme[system][bin] = finalPopulations1[bin] ; //the bin correspond to the value of the population of a specific centrality bin-1 and b for each system
    //errors1systeme[system][bin] = finalErrors1[bin];
    
      

} // To close for the bins,

	

    
    }// To close for the files

    
 
   //----------------This part will plot the populations in terms of the centrality & systems in one canvas----------------------

 
    
                       //----------------IN TERMS OF THE 4 SYSTEMS ---------
		       

  
   for (int bin = 0; bin < 8; ++bin) {//For centrality == bin
   
        
    	int binNumber = atoi(histNumber[bin].Data()); //the right value of centrtality 
	
        histo1_system[bin] = new TH1F(Form("histo1_system _%d_at 32 Mev", bin), Form("histo1_system_%d_at 32 Mev", bin), 4, 0.5, 4.5);
	

	
        for (int sys = 0; sys < 1; ++sys) {//for systems == system
	
            histo1_system[bin]->SetBinContent(sys+1, fpop1systeme[sys][bin]);
	    //histo1_system[bin]->SetBinError(sys+1, errors1systeme[sys][bin]);
            histo1_system[bin]->GetXaxis()->SetBinLabel(sys+1, systems_names_P[sys].c_str());
	  
	  

            
        }
	
      
	
        histo1_system[bin]->GetYaxis()->SetRangeUser(0.2, 1.25);
        
        histo1_system[bin]->SetMarkerStyle(markerstyles[bin]);
	histo1_system[bin]->SetMarkerSize(0.9);
        histo1_system[bin]->SetMarkerColor(colors[bin]);
	histo1_system[bin]->SetLineColor(colors[bin]);
	histo1_system[bin]->SetLineStyle(1);
	
        histo1_system[bin]->SetStats(0);
	
        histo1_system[bin]->SetTitle("The Population of the excited state of {4}^He at E = 20.21 Mev in terms of the four systems");
	histo1_system[bin]->SetTitleSize(24);
	
        
	histo1_system[bin]->GetXaxis()->SetLabelSize(0.1);
	
        histo1_system[bin]->GetYaxis()->SetTitle("Normalized Populations (%)");
	histo1_system[bin]->GetYaxis()->SetTitleSize(0.06);
	histo1_system[bin]->GetYaxis()->SetTitleOffset(0.94); 
	
	histo1_system[bin]->GetYaxis()->SetNdivisions(602,kFALSE);
	histo1_system[bin]->GetYaxis()->SetRangeUser(0, 3.7);
	
	histo1_system[bin]->GetYaxis()->SetLabelSize(0.07);
	histo1_system[bin]->GetYaxis()->SetLabelOffset(0.005);
      
	

	legend1->AddEntry(histo1_system[bin], Form("Centrality %d", binNumber), "elp");
    }
    

    TCanvas *canvas_sys = new TCanvas("canvas_sys", "Histograms of the populations in terms of the systems", 800, 600);
    canvas_sys->Divide(1,2);
    canvas_sys->cd(1);
    
    //histo1_system[0]->Draw("E1X0 LP");
   

  /*  for (int bin = 1; bin < 8; ++bin) {

        histo1_system[bin]->Draw("E1X0 LP SAME");
	
    }
    
    
    legend1->Draw("SAME");*/
	
	
  
       

   // canvas_sys->SaveAs("/scratch/dekhissi/Alpha/Populations/Populations in terms of sys for all centality_ALLCent.pdf");
   
    //canvas_sys->Write();
    
    
  	//-----------	IN TERMS OF THE CENTRALITY------------
	
gStyle->SetErrorX(0);	
 
   for (int sys = 0; sys < 1; ++sys) {
   
        histo1_centrality[sys] = new TH1F(Form("histogram2_%d", sys), Form("Histogram2_%d", sys), 8, 0, 8); //first Population

	
	
	
	
        for (int bin = 0; bin < 8; ++bin) { 
	
	int binNumber = atoi(histNumber[bin].Data());
	
            histo1_centrality[sys]->SetBinContent(bin+1, fpop1systeme[sys][bin]);
	   // histo1_centrality[sys]->SetBinError(bin+1, errors1systeme[sys][bin]);
            histo1_centrality[sys]->GetXaxis()->SetBinLabel(bin+1, Form("%d", binNumber));

	}
	
	histo1_centrality[sys]->SetMarkerSize(0.9);
        histo1_centrality[sys]->SetMarkerColor(colors[sys]);
	histo1_centrality[sys]->SetMarkerStyle(markerstyles[sys]);
	histo1_centrality[sys]->SetLineStyle(1);
	histo1_centrality[sys]->SetLineColor(colors[sys]);

        histo1_centrality[sys]->SetTitle("The Population of the excited state of {4}^He at E = 20.21 Mev in terms of the four systems");
	histo1_centrality[sys]->SetTitleSize(24);
	
        histo1_centrality[sys]->GetXaxis()->SetTitle("Centrality");
	histo1_centrality[sys]->GetXaxis()->SetLabelSize(0.1);
	
	histo1_centrality[sys]->GetXaxis()->SetTitleSize(0.06);
	histo1_centrality[sys]->GetXaxis()->SetTitleOffset(0.65);
	
	
	
	
        histo1_centrality[sys]->GetYaxis()->SetTitle("Normalized Populations (%)");
	histo1_centrality[sys]->GetYaxis()->SetTitleSize(0.06);
	histo1_centrality[sys]->GetYaxis()->SetTitleOffset(0.94); 
	
	histo1_centrality[sys]->GetYaxis()->SetLabelSize(0.07);
	histo1_centrality[sys]->GetYaxis()->SetLabelOffset(0.005);
	
	histo1_centrality[sys]->GetYaxis()->SetNdivisions(602,kFALSE);
	
	
	
	//histo1_centrality[sys]->GetYaxis()->SetRangeUser(0.2, 3.7);
 
    	histo1_centrality[sys]->SetStats(0);
	
	legend2->AddEntry(histo1_centrality[sys], Form("System %s", systems_names_P[sys].c_str()), "elp");
}

        TCanvas *canvas_centrality = new TCanvas("canvas_centrality", "Histograms of the populations in terms of the centrality", 800, 600);
        canvas_centrality->cd();
	canvas_centrality->Divide(1,2);
	canvas_centrality->cd(1);
	
	histo1_centrality[0]->Draw("E1X0 LP");
   
	legend2->Draw( "same");
	
	
 canvas_centrality->SaveAs("/scratch/dekhissi/Alpha/Populations/Populations in terms of centrality for all the systems_ALLCent.pdf");	
 canvas_centrality->Write();
 

 

			//---------------CLOSE THE OUTPUT FILE---------------------


                           outputfile->Close();



}// To close the void General_Fitting()


 
