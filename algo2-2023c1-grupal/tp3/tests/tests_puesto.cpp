#include "../src/Puesto.h"
#include "gtest-1.8.1/gtest.h"
#include <set>

using namespace std;

class PuestoTest : public testing::Test {
protected:
    Menu menu;
    Stock stock;
    Promociones descuentos;

    void SetUp() {
        menu = {
            {3, 500},
            {4, 1000},
            {5, 2500},
            {7, 2000}
        };
        stock = {
            {3, 10},
            {4, 5},
            {5, 30},
            {7, 10}
        };
        descuentos = {
            {
                7, {
                    {3, 20},
                    {6, 25}
                }
            }, {
                4, {
                    {2, 15},
                    {3, 20}
                }
            }
        };
    }
};

TEST_F(PuestoTest, descuentos) {
    Puesto p(menu, stock, descuentos);
    ASSERT_EQ(p.getDescuento(4, 1), 0);
    ASSERT_EQ(p.getDescuento(4, 2), 15);
    ASSERT_EQ(p.getDescuento(4, 3), 20);
    ASSERT_EQ(p.getDescuento(4, 4), 20);
    ASSERT_EQ(p.getDescuento(4, 5), 20);

    ASSERT_EQ(p.getDescuento(7, 2), 0);
    ASSERT_EQ(p.getDescuento(7, 3), 20);
    ASSERT_EQ(p.getDescuento(7, 5), 20);
    ASSERT_EQ(p.getDescuento(7, 6), 25);
    ASSERT_EQ(p.getDescuento(7, 90), 25);

    // El item no existe
    ASSERT_EQ(p.getDescuento(1, 5), 0);
}

TEST_F(PuestoTest, registrar_compra_sin_desc) {
    Persona p_id = 1;
    Producto i_id1 = 3;
    Producto i_id2 = 5;
    Puesto p(menu, stock, descuentos);
    ASSERT_EQ(p.getStock(i_id1), 10);

    // Registramos compra 1
    p.registrarCompraEnPuesto(p_id, i_id1, 2);

    // Disminuyó el stock
    ASSERT_EQ(p.getStock(i_id1), 8);

    // Incrementó el total para esa persona
    int total = menu[i_id1] * 2;
    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), total);

    // Registramos compra 2, misma persona
    p.registrarCompraEnPuesto(p_id, i_id2, 3);
    total = total + menu[i_id2] * 3;
    ASSERT_EQ(p.getStock(i_id2), 27);
    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), total);
}

TEST_F(PuestoTest, registrar_compra_con_desc) {
    Persona p_id = 1;
    Producto i_id = 4;
    Puesto p(menu, stock, descuentos);

    p.registrarCompraEnPuesto(p_id, i_id, 2);

    int total = menu[i_id] * 2 * 0.85;
    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), total);
}

TEST_F(PuestoTest, registrar_compra_mixta) {
    Persona p_id = 1;
    Producto i_id = 4;
    Puesto p(menu, stock, descuentos);

    p.registrarCompraEnPuesto(p_id, i_id, 1);

    int total = menu[i_id];
    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), total);
    ASSERT_EQ(p.getStock(i_id), 4);

    p.registrarCompraEnPuesto(p_id, i_id, 2);

    total += menu[i_id] * 2 * 0.85;
    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), total);
    ASSERT_EQ(p.getStock(i_id), 2);
}

TEST_F(PuestoTest, hackear_happy_path) {
    Persona p_id = 1;
    Producto i_id = 3;
    Puesto p(menu, stock, descuentos);

    // Registramos compra
    p.registrarCompraEnPuesto(p_id, i_id, 2);

    ASSERT_EQ(p.getStock(i_id), 8);
    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), menu[i_id] * 2);

    // Hackeamos
    p.hackearPuesto(p_id, i_id);

    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), menu[i_id]);
    ASSERT_EQ(p.getStock(i_id), 9);

    // Volvemos a hackear, debería haber desaparecido la venta
    p.hackearPuesto(p_id, i_id);

    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), 0);
    ASSERT_EQ(p.getStock(i_id), 10);
}

TEST_F(PuestoTest, hackear_mixto) {
    Persona p_id = 1;
    Producto i_id = 7;
    Puesto p(menu, stock, descuentos);

    p.registrarCompraEnPuesto(p_id, i_id, 1);  // Sin descuento
    p.registrarCompraEnPuesto(p_id, i_id, 3);  // Con descuento
    p.registrarCompraEnPuesto(p_id, i_id, 2);  // Sin descuento

    int total = 3 * menu[i_id] + 3 * menu[i_id] * 0.80;
    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), total);
    ASSERT_EQ(p.getStock(i_id), 4);

    // Hackeamos
    p.hackearPuesto(p_id, i_id);
    p.hackearPuesto(p_id, i_id);
    p.hackearPuesto(p_id, i_id);

    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), 3 * menu[i_id] * 0.80);
    ASSERT_EQ(p.getStock(i_id), 7);

    // Volvemos a comprar y hackear para verificar que no quedaron referencias
    // colgadas ni iteradores invalidados.
    p.registrarCompraEnPuesto(p_id, i_id, 1);

    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), 3 * menu[i_id] * 0.80 + menu[i_id]);
    ASSERT_EQ(p.getStock(i_id), 6);

    p.hackearPuesto(p_id, i_id);

    ASSERT_EQ(p.getGastoPorPersonaEnPuesto(p_id), 3 * menu[i_id] * 0.80);
    ASSERT_EQ(p.getStock(i_id), 7);
}