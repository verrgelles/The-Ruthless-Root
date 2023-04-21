#include <iostream>

using namespace std;

int max_energy = 134; // MEV
int speed_of_light = 1;

auto Generator(int max_energy, int speed_of_light, int particle_number)
{
    auto r = new TRandom(0);

    double E_1, E_2, P_1, P_2, phi_1, phi_2, rho_1, rho_2;

    E_1 = r->Uniform(1, max_energy);
    E_2 = max_energy - E_1;

    P_1 = E_1 / 2 * speed_of_light;
    P_2 = E_2 / 2 * speed_of_light;

    phi_1 = r->Uniform(1, 2 * TMath::Pi());
    phi_2 = phi_1 + TMath::Pi();

    rho_1 = r->Uniform(1, 2 * TMath::Pi());
    rho_2 = rho_1 + TMath::Pi();

    double ptc1_px = P_1 * TMath::Cos(phi_1);
    double ptc1_py = P_1 * TMath::Sin(phi_1);
    double ptc1_pz = TMath::Sqrt(P_1 * P_1 - (ptc1_px * ptc1_px + ptc1_py * ptc1_py));

    double ptc2_px = P_2 * TMath::Cos(phi_2);
    double ptc2_py = P_2 * TMath::Sin(phi_2);
    double ptc2_pz = TMath::Sqrt(P_2 * P_2 - (ptc2_px * ptc2_px + ptc2_py * ptc2_py));

    ROOT::Math::PxPyPzEVector ptc1(ptc1_px, ptc1_py, ptc1_pz, E_1);
    ROOT::Math::PxPyPzEVector ptc2(ptc2_px, ptc2_py, ptc2_pz, E_2);

    if (particle_number == 1)
        return ptc1;
    else
        return ptc2;
}

int Main()
{
    TCanvas *c1 = new TCanvas();

    TH1D *hist = new TH1D("hist", "Histro", 5000, 1, 134);

    for (int i = 0; i < 5000; i++)
    {
        auto ptc_1 = Generator(max_energy, speed_of_light, 1);
        auto ptc_2 = Generator(max_energy, speed_of_light, 2);

        hist->Fill(ptc_1.E());
    }

    hist->GetXaxis()->SetTitle("E");
    hist->GetYaxis()->SetTitle("Number of particles");

    hist->Draw();

    return 0;
}