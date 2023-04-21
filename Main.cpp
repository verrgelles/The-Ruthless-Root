#include <iostream>
#include <vector>

using namespace std;

int max_energy = 134; // in MEv

auto Generator(int max_energy, int speed_of_light, int particle_number)
{
    bool f = 0;
    auto rand = new TRandom3();

    double E_1, E_2, P_1, P_2, phi_1, phi_2, rho_1, rho_2;

    while (f)
    {
        E_1 = rand->Rndm() * 100;
        if (E_1 > 0 && E_1 < max_energy)
        {
            E_2 = max_energy - E_1;

            P_1 = E_1 / 2 * speed_of_light;
            P_2 = E_2 / 2 * speed_of_light;

            f = 1;
        }
    };

    f = 0;
    while (f)
    {
        phi_1 = rand->Rndm() * 1.5;
        if (phi_1 > 0 && phi_1 < 2 * TMath::Pi())
        {
            phi_2 = phi_1 + TMath::Pi();
            f = 1;
        }
    };

    f = 0;
    while (f)
    {
        rho_1 = rand->Rndm() * 1.5;
        if (rho_1 > 0 && rho_1 < 2 * TMath::Pi())
        {
            rho_2 = rho_2 + TMath::Pi();
            f = 1;
        }
    }

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

    return 0;
}