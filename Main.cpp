#include <iostream>

using namespace std;

// Global consts
const int max_energy = 134; // MEV
const int speed_of_light = 1;

// Particles params
double ptc1_p, ptc1_px, ptc1_py, ptc1_pz, ptc1_e, ptc1_tha, ptc1_phi;
double ptc2_p, ptc2_px, ptc2_py, ptc2_pz, ptc2_e, ptc2_tha, ptc2_phi;

// Places generated data in particles params
void dataGenerator()
{
    auto r = new TRandom(0);

    ptc1_e = r->Uniform(1, max_energy);
    ptc2_e = max_energy - ptc1_e;

    ptc1_p = ptc1_e / (2 * speed_of_light);
    ptc2_p = ptc2_e / (2 * speed_of_light);

    ptc1_tha = r->Uniform(0, TMath::Pi());
    ptc2_tha = TMath::Abs(ptc1_tha - TMath::Pi());

    ptc1_phi = r->Uniform(-TMath::Pi(), TMath::Pi());
    ptc2_phi = ptc1_phi + TMath::Pi();

    ptc1_px = ptc1_p * TMath::Cos(ptc1_tha);
    ptc1_py = ptc1_p * TMath::Sin(ptc2_tha);
    ptc1_pz = TMath::Sqrt(ptc1_p * ptc1_p - (ptc1_px * ptc1_px + ptc1_py * ptc1_py));

    ptc2_px = ptc2_p * TMath::Cos(ptc1_phi);
    ptc2_py = ptc2_p * TMath::Sin(ptc2_phi);
    ptc2_pz = TMath::Sqrt(ptc1_p * ptc1_p - (ptc2_px * ptc2_px + ptc2_py * ptc2_py));
}

// Generates .root files with particles params. N - number of samples
void fileGenerator(int N)
{
    TFile *output1 = new TFile("ptc1.root", "recreate");
    TTree *ptc1_tree = new TTree();

    ptc1_tree->Branch("Px", &ptc1_px, "ptc1_px/D");
    ptc1_tree->Branch("Py", &ptc1_py, "ptc1_py/D");
    ptc1_tree->Branch("Pz", &ptc1_pz, "ptc1_pz/D");
    ptc1_tree->Branch("E", &ptc1_e, "ptc1_e/D");
    ptc1_tree->Branch("theta", &ptc1_tha, "ptc1_tha/D");
    ptc1_tree->Branch("phi", &ptc1_phi, "ptc1_phi/D");

    for (int i = 0; i < N; i++)
    {
        dataGenerator();
        ptc1_tree->Fill();
    }
    // ptc1_tree->StartViewer();
    output1->Write();
    output1->Close();

    TFile *output2 = new TFile("ptc2.root", "recreate");
    TTree *ptc2_tree = new TTree();

    ptc2_tree->Branch("Px", &ptc2_px, "ptc2_px/D");
    ptc2_tree->Branch("Py", &ptc2_py, "ptc2_py/D");
    ptc2_tree->Branch("Pz", &ptc2_pz, "ptc2_pz/D");
    ptc2_tree->Branch("E", &ptc2_e, "ptc2_e/D");
    ptc2_tree->Branch("theta", &ptc2_tha, "ptc2_tha/D");
    ptc2_tree->Branch("phi", &ptc2_phi, "ptc2_phi/D");

    for (int i = 0; i < N; i++)
    {
        dataGenerator();
        ptc2_tree->Fill();
    }
    // ptc2_tree->StartViewer();
    output2->Write();
    output2->Close();
}

/*void createHist()
{
    TFile *input1 = new TFile("ptc1.root", "read");
    TTree *ptc1_tree = (TTree *)input1->Get();

    ptc1_tree->SetBranchAddress("Px", &ptc1_px, "ptc1_px/D");
    ptc1_tree->SetBranchAddress("Py", &ptc1_py, "ptc1_py/D");
    ptc1_tree->SetBranchAddress("Pz", &ptc1_pz, "ptc1_pz/D");
    ptc1_tree->SetBranchAddress("E", &ptc1_e, "ptc1_e/D");
    ptc1_tree->SetBranchAddress("theta", &ptc1_tha, "ptc1_tha/D");
    ptc1_tree->SetBranchAddress("phi", &ptc1_phi, "ptc1_phi/D");

    int N = ptc1_tree->GetEntries();

    double min, max = 0;

    for (int i = 0; i < N; i++)
    {
        ptc1_tree->GetEntry(i);
        if (ptc1_px > max)
        {
            max = ptc1_px;
        }
        if (min > ptc1_px)
        {
            min = ptc1_px;
        }
    }

    TCanvas *c1 = new TCanvas();

    TH1F *hist = new TH1F("hist", "hist", N, min, max);

    for (int i = 0; i < N; i++)
    {
        ptc1_tree->GetEntry(i);
        hist->Fill(ptc1_px);
    }

    hist->Draw();
}*/

int Main()
{
    fileGenerator(10000);
    return 0;
}

/*ROOT::Math::PxPyPzEVector ptc1(ptc1_px, ptc1_py, ptc1_pz, E_1);
    ROOT::Math::Polar3DVector ptc1_agl(P_1, theta_1, phi_1);
    ROOT::Math::PxPyPzEVector ptc2(ptc2_px, ptc2_py, ptc2_pz, E_2);
    ROOT::Math::Polar3DVector ptc2_agl(P_2, theta_2, phi_2);*/
