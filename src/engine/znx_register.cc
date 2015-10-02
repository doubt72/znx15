#include <iostream>

#include "znx_register.h"

znx_register::znx_register() {
  int z, w;

  _i = new unsigned int[ZNX_I32_COUNT];
  _d = new unsigned int[ZNX_D32_COUNT];
  _si = new unsigned int[ZNX_I32_COUNT];
  _sd = new unsigned int[ZNX_D32_COUNT - 1];
  _f = new double [ZNX_F64_COUNT];
  _m = new unsigned int *[ZNX_SIMD_COUNT];

  for (z = 0; z < ZNX_I32_COUNT; z++) {
    _i[z] = 0;
    _si[z] = 0;
  }
  for (z = 0; z < ZNX_D32_COUNT; z++) {
    _d[z] = 0;
    if (z < ZNX_D32_COUNT - 1) {
      _sd[z] = 0;
    }
  }
  for (z = 0; z < ZNX_F64_COUNT; z++) {
    _f[z] = 0.0;
  }
  for (z = 0; z < ZNX_SIMD_COUNT; z++) {
    _m[z] = new unsigned int[ZNX_SIMD_DEPTH];
    for (w = 0; w < ZNX_SIMD_DEPTH; w++) {
      _m[z][w] = 0;
    }
  }

  s_mode = true;

  u_zero = false;
  u_neg = false;
  u_oflow = false;
  u_carry = false;
  u_fzero = false;
  u_fneg = false;
  u_inf = false;
  u_neg_inf = false;
  u_nan = false;
  u_denorm = false;

  s_zero = false;
  s_neg = false;
  s_oflow = false;
  s_carry = false;
  s_fzero = false;
  s_fneg = false;
  s_inf = false;
  s_neg_inf = false;
  s_nan = false;
  s_denorm = false;

  _asn = 0;

  _d[ZNX_D32_COUNT - 1] = 1; 
}

bool znx_register::sup_mode() {
  return s_mode;
}
void znx_register::set_sup_mode() {
  s_mode = true;
}
void znx_register::clr_sup_mode() {
  s_mode = false;
}

bool znx_register::zero() {
  return s_mode ? s_zero : u_zero;
}
bool znx_register::neg() {
  return s_mode ? s_neg : u_neg;
}
bool znx_register::oflow() {
  return s_mode ? s_oflow : u_oflow;
}
bool znx_register::carry() {
  return s_mode ? s_carry : u_carry;
}
bool znx_register::fzero() {
  return s_mode ? s_fzero : u_fzero;
}
bool znx_register::fneg() {
  return s_mode ? s_fneg : u_fneg;
}
bool znx_register::inf() {
  return s_mode ? s_inf : u_inf;
}
bool znx_register::neg_inf() {
  return s_mode ? s_neg_inf : u_neg_inf;
}
bool znx_register::nan() {
  return s_mode ? s_nan : u_nan;
}
bool znx_register::denorm() {
  return s_mode ? s_denorm : u_denorm;
}

void znx_register::set_zero() {
  if (s_mode) {
    s_zero = true;
  } else {
    u_zero = true;
  }
}
void znx_register::set_neg() {
  if (s_mode) {
    s_neg = true;
  } else {
    u_neg = true;
  }
}
void znx_register::set_oflow() {
  if (s_mode) {
    s_oflow = true;
  } else {
    u_oflow = true;
  }
}
void znx_register::set_carry() {
  if (s_mode) {
    s_carry = true;
  } else {
    u_carry = true;
  }
}
void znx_register::set_fzero() {
  if (s_mode) {
    s_fzero = true;
  } else {
    u_fzero = true;
  }
}
void znx_register::set_fneg() {
  if (s_mode) {
    s_fneg = true;
  } else {
    u_fneg = true;
  }
}
void znx_register::set_inf() {
  if (s_mode) {
    s_inf = true;
  } else {
    u_inf = true;
  }
}
void znx_register::set_neg_inf() {
  if (s_mode) {
    s_neg_inf = true;
  } else {
    u_neg_inf = true;
  }
}
void znx_register::set_nan() {
  if (s_mode) {
    s_nan = true;
  } else {
    u_nan = true;
  }
}
void znx_register::set_denorm() {
  if (s_mode) {
    s_denorm = true;
  } else {
    u_denorm = true;
  }
}

void znx_register::clr_zero() {
  if (s_mode) {
    s_zero = false;
  } else {
    u_zero = false;
  }
}
void znx_register::clr_neg() {
  if (s_mode) {
    s_neg = false;
  } else {
    u_neg = false;
  }
}
void znx_register::clr_oflow() {
  if (s_mode) {
    s_oflow = false;
  } else {
    u_oflow = false;
  }
}
void znx_register::clr_carry() {
  if (s_mode) {
    s_carry = false;
  } else {
    u_carry = false;
  }
}
void znx_register::clr_fzero() {
  if (s_mode) {
    s_fzero = false;
  } else {
    u_fzero = false;
  }
}
void znx_register::clr_fneg() {
  if (s_mode) {
    s_fneg = false;
  } else {
    u_fneg = false;
  }
}
void znx_register::clr_inf() {
  if (s_mode) {
    s_inf = false;
  } else {
    u_inf = false;
  }
}
void znx_register::clr_neg_inf() {
  if (s_mode) {
    s_neg_inf = false;
  } else {
    u_neg_inf = false;
  }
}
void znx_register::clr_nan() {
  if (s_mode) {
    s_nan = false;
  } else {
    u_nan = false;
  }
}
void znx_register::clr_denorm() {
  if (s_mode) {
    s_denorm = false;
  } else {
    u_denorm = false;
  }
}

unsigned int znx_register::status() {
  unsigned int rc = 0;
  if (zero()) {
    rc = 1;
  }
  if (neg()) {
    rc += 2;
  }
  if (oflow()) {
    rc += 4;
  }
  if (carry()) {
    rc += 8;
  }
  if (fzero()) {
    rc += 16;
  }
  if (fneg()) {
    rc += 32;
  }
  if (inf()) {
    rc += 64;
  }
  if (neg_inf()) {
    rc += 128;
  }
  if (nan()) {
    rc += 256;
  }
  if (denorm()) {
    rc += 512;
  }
  return rc;
}

void znx_register::set_status(unsigned int value) {
  if (value & 1) {
    set_zero();
  } else {
    clr_zero();
  }
  if (value & 2) {
    set_neg();
  } else {
    clr_neg();
  }
  if (value & 4) {
    set_oflow();
  } else {
    clr_oflow();
  }
  if (value & 8) {
    set_carry();
  } else {
    clr_carry();
  }
  if (value & 16) {
    set_fzero();
  } else {
    clr_fzero();
  }
  if (value & 32) {
    set_fneg();
  } else {
    clr_fneg();
  }
  if (value & 64) {
    set_inf();
  } else {
    clr_inf();
  }
  if (value & 128) {
    set_neg_inf();
  } else {
    clr_neg_inf();
  }
  if (value & 256) {
    set_nan();
  } else {
    clr_nan();
  }
  if (value & 512) {
    set_denorm();
  } else {
    clr_denorm();
  }
}

unsigned int znx_register::i(int index) {
  if (index < 0 || index >= ZNX_I32_COUNT) {
    return 0;
  }
  if (s_mode) {
    return _si[index];
  } else {
    return _i[index];
  }
}
void znx_register::set_i(int index, unsigned int value) {
  if (index < 0 || index >= ZNX_I32_COUNT) {
    return;
  }
  if (s_mode) {
    _si[index] = value;
  } else {
    _i[index] = value;
  }
}

unsigned int znx_register::d(int index) {
  if (index < 0 || index >= ZNX_D32_COUNT) {
    return 0;
  }
  if (s_mode) {
    if (index < ZNX_D32_COUNT - 1) {
      return _sd[index];
    } else {
      return _d[index];
    }
  } else {
    return _d[index];
  }
}
void znx_register::set_d(int index, unsigned int value) {
  if (index < 0 || index >= ZNX_D32_COUNT) {
    return;
  }
  if (s_mode) {
    if (index < ZNX_D32_COUNT - 1) {
      _sd[index] = value;
    } else {
      _d[index] = value;
    }
  } else {
    _d[index] = value;
  }
}

double znx_register::f(int index) {
  if (index < 0 || index >= ZNX_F64_COUNT) {
    return 0;
  }
  return _f[index];
}
void znx_register::set_f(int index, double value) {
  if (index < 0 || index >= ZNX_F64_COUNT) {
    return;
  }
  _f[index] = value;
}

unsigned int* znx_register::m(int index) {
  if (index < 0 || index >= ZNX_SIMD_COUNT) {
    return 0;
  }
  int z;
  unsigned int *rc = new unsigned int[ZNX_SIMD_DEPTH];
  for (z = 0; z < ZNX_SIMD_DEPTH; z++) {
    rc[z] = _m[index][z];
  }
  return rc;
}
void znx_register::set_m(int index, unsigned int* value) {
  if (index < 0 || index >= ZNX_SIMD_COUNT) {
    return;
  }
  int z;
  for (z = 0; z < ZNX_SIMD_DEPTH; z++) {
    _m[index][z] = value[z];
  }
}

unsigned int znx_register::sp() {
  if (s_mode) {
    return _sd[ZNX_D32_COUNT - 2];
  } else {
    return _d[ZNX_D32_COUNT - 2];
  }
}
void znx_register::set_sp(unsigned int value) {
  if (s_mode) {
    _sd[ZNX_D32_COUNT - 2] = value;
  } else {
    _d[ZNX_D32_COUNT - 2] = value;
  }
}

unsigned int znx_register::pc() {
  return _d[ZNX_D32_COUNT - 1];
}
void znx_register::set_pc(unsigned int value) {
  _d[ZNX_D32_COUNT - 1] = value;
}

unsigned int znx_register::lr() {
  if (s_mode) {
    return _si[ZNX_D32_COUNT - 1];
  } else {
    return _i[ZNX_D32_COUNT - 1];
  }
}
void znx_register::set_lr(unsigned int value) {
  if (s_mode) {
    _si[ZNX_D32_COUNT - 1] = value;
  } else {
    _i[ZNX_D32_COUNT - 1] = value;
  }
}

unsigned int znx_register::asn() {
  return _asn;
}
void znx_register::set_asn(unsigned int value) {
  _asn = value;
}

std::string chok(bool ok) {
  if (ok) {
    return "OK\n";
  } else {
    return "FAIL\n";
  }
}

void znx_register::system_check() {
  // Size checks
  bool ok = true;
  int size = sizeof(_i[0]) * 8;
  if (size != 32) { ok = false; }
  std::cout << "32-bit register size: " << size;
  std::cout << " ................check: " + chok(ok);

  ok = true;
  size = sizeof(_f[0]) * 8;
  if (size != 64) { ok = false; }
  std::cout << "64-bit register size: " << size;
  std::cout << " ................check: " + chok(ok);

  ok = true;
  size = sizeof(m(0)[0]) * ZNX_SIMD_DEPTH * 8;
  if (size != 256) { ok = false; }
  std::cout << "SIMD register size: " << size;
  std::cout << " (256) ...........check: " + chok(ok);

  // Check the supervisor mode bit settings
  ok = true;
  if (!sup_mode()) { ok = false; }
  clr_sup_mode(); if (sup_mode()) { ok = false; }
  set_sup_mode(); if (!sup_mode()) { ok = false; }
  std::cout << "register: supervisor mode................check: " << chok(ok);

  // Check all of the individual status flag settings
  ok = true;
  if (zero()) { ok = false; }
  set_zero(); if (!zero()) { ok = false; }
  clr_sup_mode(); if (zero()) { ok = false; }
  set_zero(); if (!zero()) { ok = false; }
  clr_zero(); if (zero()) { ok = false; }
  set_sup_mode(); if (!zero()) { ok = false; }
  clr_zero(); if (zero()) { ok = false; }

  if (neg()) { ok = false; }
  set_neg(); if (!neg()) { ok = false; }
  clr_sup_mode(); if (neg()) { ok = false; }
  set_neg(); if (!neg()) { ok = false; }
  clr_neg(); if (neg()) { ok = false; }
  set_sup_mode(); if (!neg()) { ok = false; }
  clr_neg(); if (neg()) { ok = false; }

  if (oflow()) { ok = false; }
  set_oflow(); if (!oflow()) { ok = false; }
  clr_sup_mode(); if (oflow()) { ok = false; }
  set_oflow(); if (!oflow()) { ok = false; }
  clr_oflow(); if (oflow()) { ok = false; }
  set_sup_mode(); if (!oflow()) { ok = false; }
  clr_oflow(); if (oflow()) { ok = false; }

  if (carry()) { ok = false; }
  set_carry(); if (!carry()) { ok = false; }
  clr_sup_mode(); if (carry()) { ok = false; }
  set_carry(); if (!carry()) { ok = false; }
  clr_carry(); if (carry()) { ok = false; }
  set_sup_mode(); if (!carry()) { ok = false; }
  clr_carry(); if (carry()) { ok = false; }

  if (fzero()) { ok = false; }
  set_fzero(); if (!fzero()) { ok = false; }
  clr_sup_mode(); if (fzero()) { ok = false; }
  set_fzero(); if (!fzero()) { ok = false; }
  clr_fzero(); if (fzero()) { ok = false; }
  set_sup_mode(); if (!fzero()) { ok = false; }
  clr_fzero(); if (fzero()) { ok = false; }

  if (fneg()) { ok = false; }
  set_fneg(); if (!fneg()) { ok = false; }
  clr_sup_mode(); if (fneg()) { ok = false; }
  set_fneg(); if (!fneg()) { ok = false; }
  clr_fneg(); if (fneg()) { ok = false; }
  set_sup_mode(); if (!fneg()) { ok = false; }
  clr_fneg(); if (fneg()) { ok = false; }

  if (inf()) { ok = false; }
  set_inf(); if (!inf()) { ok = false; }
  clr_sup_mode(); if (inf()) { ok = false; }
  set_inf(); if (!inf()) { ok = false; }
  clr_inf(); if (inf()) { ok = false; }
  set_sup_mode(); if (!inf()) { ok = false; }
  clr_inf(); if (inf()) { ok = false; }

  if (neg_inf()) { ok = false; }
  set_neg_inf(); if (!neg_inf()) { ok = false; }
  clr_sup_mode(); if (neg_inf()) { ok = false; }
  set_neg_inf(); if (!neg_inf()) { ok = false; }
  clr_neg_inf(); if (neg_inf()) { ok = false; }
  set_sup_mode(); if (!neg_inf()) { ok = false; }
  clr_neg_inf(); if (neg_inf()) { ok = false; }

  if (nan()) { ok = false; }
  set_nan(); if (!nan()) { ok = false; }
  clr_sup_mode(); if (nan()) { ok = false; }
  set_nan(); if (!nan()) { ok = false; }
  clr_nan(); if (nan()) { ok = false; }
  set_sup_mode(); if (!nan()) { ok = false; }
  clr_nan(); if (nan()) { ok = false; }

  if (denorm()) { ok = false; }
  set_denorm(); if (!denorm()) { ok = false; }
  clr_sup_mode(); if (denorm()) { ok = false; }
  set_denorm(); if (!denorm()) { ok = false; }
  clr_denorm(); if (denorm()) { ok = false; }
  set_sup_mode(); if (!denorm()) { ok = false; }
  clr_denorm(); if (denorm()) { ok = false; }

  // Check status register load/unload; make sure flags match
  if (status()) { ok = false; }
  unsigned int check = 1023;

  set_status(check);
  if (status() != check) { ok = false; }
  if (!zero()) { ok = false; }
  if (!neg()) { ok = false; }
  if (!oflow()) { ok = false; }
  if (!carry()) { ok = false; }
  if (!fzero()) { ok = false; }
  if (!fneg()) { ok = false; }
  if (!inf()) { ok = false; }
  if (!neg_inf()) { ok = false; }
  if (!nan()) { ok = false; }
  if (!denorm()) { ok = false; }

  // Make sure supervisor/user mode status are distinct
  clr_sup_mode();
  if (status() != 0) { ok = false; }
  if (zero()) { ok = false; }
  if (neg()) { ok = false; }
  if (oflow()) { ok = false; }
  if (carry()) { ok = false; }
  if (fzero()) { ok = false; }
  if (fneg()) { ok = false; }
  if (inf()) { ok = false; }
  if (neg_inf()) { ok = false; }
  if (nan()) { ok = false; }
  if (denorm()) { ok = false; }

  set_status(check);
  if (status() != check) { ok = false; }
  if (!zero()) { ok = false; }
  if (!neg()) { ok = false; }
  if (!oflow()) { ok = false; }
  if (!carry()) { ok = false; }
  if (!fzero()) { ok = false; }
  if (!fneg()) { ok = false; }
  if (!inf()) { ok = false; }
  if (!neg_inf()) { ok = false; }
  if (!nan()) { ok = false; }
  if (!denorm()) { ok = false; }

  // Reset and check
  set_status(0);
  if (status() != 0) { ok = false; }
  if (zero()) { ok = false; }
  if (neg()) { ok = false; }
  if (oflow()) { ok = false; }
  if (carry()) { ok = false; }
  if (fzero()) { ok = false; }
  if (fneg()) { ok = false; }
  if (inf()) { ok = false; }
  if (neg_inf()) { ok = false; }
  if (nan()) { ok = false; }
  if (denorm()) { ok = false; }

  // Reset and check supervisor mode
  set_sup_mode();
  if (!zero()) { ok = false; }
  if (!neg()) { ok = false; }
  if (!oflow()) { ok = false; }
  if (!carry()) { ok = false; }
  if (!fzero()) { ok = false; }
  if (!fneg()) { ok = false; }
  if (!inf()) { ok = false; }
  if (!neg_inf()) { ok = false; }
  if (!nan()) { ok = false; }
  if (!denorm()) { ok = false; }

  set_status(0);
  if (status() != 0) { ok = false; }
  if (zero()) { ok = false; }
  if (neg()) { ok = false; }
  if (oflow()) { ok = false; }
  if (carry()) { ok = false; }
  if (fzero()) { ok = false; }
  if (fneg()) { ok = false; }
  if (inf()) { ok = false; }
  if (neg_inf()) { ok = false; }
  if (nan()) { ok = false; }
  if (denorm()) { ok = false; }
  std::cout << "register: status register................check: " << chok(ok);

  // Check setting the integer registers
  ok = true;
  int z, w;
  for (z = 0; z < ZNX_I32_COUNT; z++) {
    if (i(z) != 0) { ok = false; }
  }
  for (z = 0; z < ZNX_I32_COUNT; z++) {
    set_i(z, z + 7);
  }
  for (z = 0; z < ZNX_I32_COUNT; z++) {
    if (i(z) != z + 7) { ok = false; }
  }

  for (z = 0; z < ZNX_D32_COUNT - 1; z++) {
    if (d(z) != 0) { ok = false; }
  }
  // %df/%pc is initialized at 1
  if (d(ZNX_D32_COUNT - 1) != 1) { ok = false; }
  for (z = 0; z < ZNX_D32_COUNT; z++) {
    set_d(z, z + 7);
  }
  for (z = 0; z < ZNX_D32_COUNT; z++) {
    if (d(z) != z + 7) { ok = false; }
  }

  // Check that user/supervisor registers are distinct
  clr_sup_mode();
  for (z = 0; z < ZNX_I32_COUNT; z++) {
    if (i(z) != 0) { ok = false; }
  }
  for (z = 0; z < ZNX_D32_COUNT - 1; z++) {
    if (d(z) != 0) { ok = false; }
  }
  // %df/%pc doesn't change for mode shifts/is shared
  if (d(ZNX_D32_COUNT - 1) != ZNX_D32_COUNT + 6) { ok = false; }

  for (z = 0; z < ZNX_I32_COUNT; z++) {
    set_i(z, z + 7);
  }
  for (z = 0; z < ZNX_I32_COUNT; z++) {
    if (i(z) != z + 7) { ok = false; }
    set_i(z, 0);
    if (i(z) != 0) { ok = false; }
  }
  for (z = 0; z < ZNX_D32_COUNT; z++) {
    set_d(z, z + 7);
  }
  for (z = 0; z < ZNX_D32_COUNT; z++) {
    if (d(z) != z + 7) { ok = false; }
    set_d(z, 0);
    if (d(z) != 0) { ok = false; }
  }
  // Reset and check supervisor mode
  set_sup_mode();
  for (z = 0; z < ZNX_I32_COUNT; z++) {
    if (i(z) != z + 7) { ok = false; }
    set_i(z, 0);
    if (i(z) != 0) { ok = false; }
  }
  for (z = 0; z < ZNX_D32_COUNT - 1; z++) {
    if (d(z) != z + 7) { ok = false; }
    set_d(z, 0);
    if (d(z) != 0) { ok = false; }
  }
  if (d(ZNX_D32_COUNT - 1) != 0) { ok = false; }
  set_d(ZNX_D32_COUNT - 1, 1);
  if (d(ZNX_D32_COUNT - 1) != 1) { ok = false; }
  std::cout << "register: integer registers..............check: " << chok(ok);

  // Check the floating point registers
  ok = true;
  for (z = 0; z < ZNX_F64_COUNT; z++) {
    if (f(z) != 0) { ok = false; }
  }
  for (z = 0; z < ZNX_F64_COUNT; z++) {
    set_f(z, z + 7.7);
  }
  for (z = 0; z < ZNX_F64_COUNT; z++) {
    if (f(z) != z + 7.7) { ok = false; }
  }

  // Verify that user mode is not distinct
  clr_sup_mode();
  for (z = 0; z < ZNX_F64_COUNT; z++) {
    if (f(z) != z + 7.7) { ok = false; }
  }
  set_sup_mode();

  // Clear and check
  for (z = 0; z < ZNX_F64_COUNT; z++) {
    if (f(z) != z + 7.7) { ok = false; }
    set_f(z, 0);
    if (f(z) != 0) { ok = false; }
  }
  std::cout << "register: floating point registers.......check: " << chok(ok);

  // Check the SIMD registers
  ok = true;
  for (z = 0; z < ZNX_SIMD_COUNT; z++) {
    unsigned int *rc = m(z);
    for (w = 0; w < ZNX_SIMD_DEPTH; w++) {
      if (rc[w] != 0) { ok = false; }
    }
  }

  // Set up value to copy into the registers
  unsigned int *check_m = new unsigned int[ZNX_SIMD_DEPTH];
  for (z = 0; z < ZNX_SIMD_DEPTH; z++) {
    check_m[z] = z + 7;
  }
  // Copy and verify
  for (z = 0; z < ZNX_SIMD_COUNT; z++) {
    set_m(z, check_m);
  }
  for (z = 0; z < ZNX_SIMD_COUNT; z++) {
    unsigned int *rc = m(z);
    for (w = 0; w < ZNX_SIMD_DEPTH; w++) {
      if (rc[w] != w + 7) { ok = false; }
    }
  }

  // Verify that user mode is not distinct
  clr_sup_mode();
  for (z = 0; z < ZNX_SIMD_COUNT; z++) {
    unsigned int *rc = m(z);
    for (w = 0; w < ZNX_SIMD_DEPTH; w++) {
      if (rc[w] != w + 7) { ok = false; }
    }
  }
  set_sup_mode();

  // Clear and check
  for (z = 0; z < ZNX_SIMD_DEPTH; z++) {
    check_m[z] = 0;
  }
  for (z = 0; z < ZNX_SIMD_COUNT; z++) {
    unsigned int *rc = m(z);
    for (w = 0; w < ZNX_SIMD_DEPTH; w++) {
      if (rc[w] != w + 7) { ok = false; }
    }
    set_m(z, check_m);
    rc = m(z);
    for (w = 0; w < ZNX_SIMD_DEPTH; w++) {
      if (rc[w] != 0) { ok = false; }
    }
  }
  // Clean up our temporary data
  free(check_m);
  std::cout << "register: SIMD registers.................check: " << chok(ok);

  ok = true;
  // Stack pointer
  if (sp()) { ok = false; }
  set_sp(7); if (sp() != 7) { ok = false; }
  // User and supervisor pointers are distinct
  clr_sup_mode(); if (sp()) { ok = false; }
  set_sp(7); if (sp() != 7) { ok = false; }
  set_sp(0); if (sp()) { ok = false; }
  set_sup_mode(); if (sp() != 7) { ok = false; }
  set_sp(0); if (sp()) { ok = false; }

  // Test shared register
  if (sp()) { ok = false; }
  set_d(ZNX_D32_COUNT - 2, 7); if (sp() != 7) { ok = false; }
  // User and supervisor pointers are distinct
  clr_sup_mode(); if (sp()) { ok = false; }
  set_d(ZNX_D32_COUNT - 2, 7); if (sp() != 7) { ok = false; }
  set_d(ZNX_D32_COUNT - 2, 0); if (sp()) { ok = false; }
  set_sup_mode(); if (sp() != 7) { ok = false; }
  set_d(ZNX_D32_COUNT - 2, 0); if (sp()) { ok = false; }

  if (d(ZNX_D32_COUNT - 2)) { ok = false; }
  set_sp(7); if (d(ZNX_D32_COUNT - 2) != 7) { ok = false; }
  // User and supervisor pointers are distinct
  clr_sup_mode(); if (d(ZNX_D32_COUNT - 2)) { ok = false; }
  set_sp(7); if (d(ZNX_D32_COUNT - 2) != 7) { ok = false; }
  set_sp(0); if (d(ZNX_D32_COUNT - 2)) { ok = false; }
  set_sup_mode(); if (d(ZNX_D32_COUNT - 2) != 7) { ok = false; }
  set_sp(0); if (d(ZNX_D32_COUNT - 2)) { ok = false; }

  // Program counter
  if (pc() != 1) { ok = false; }
  set_pc(7); if (pc() != 7) { ok = false; }
  // User and supervisor program counters are NOT distinct
  clr_sup_mode(); if (pc() != 7) { ok = false; }
  set_pc(0); if (pc()) { ok = false; }
  set_pc(7); if (pc() != 7) { ok = false; }
  set_sup_mode(); if (pc() != 7) { ok = false; }
  set_pc(1); if (pc() != 1) { ok = false; }

  // Test shared register
  if (pc() != 1) { ok = false; }
  set_d(ZNX_D32_COUNT - 1, 7); if (pc() != 7) { ok = false; }
  // User and supervisor program counters are NOT distinct
  clr_sup_mode(); if (pc() != 7) { ok = false; }
  set_d(ZNX_D32_COUNT - 1, 0); if (pc()) { ok = false; }
  set_d(ZNX_D32_COUNT - 1, 7); if (pc() != 7) { ok = false; }
  set_sup_mode(); if (pc() != 7) { ok = false; }
  set_d(ZNX_D32_COUNT - 1, 1); if (pc() != 1) { ok = false; }

  if (d(ZNX_D32_COUNT - 1) != 1) { ok = false; }
  set_pc(7); if (d(ZNX_D32_COUNT - 1) != 7) { ok = false; }
  // User and supervisor program counters are NOT distinct
  clr_sup_mode(); if (d(ZNX_D32_COUNT - 1) != 7) { ok = false; }
  set_pc(0); if (d(ZNX_D32_COUNT - 1)) { ok = false; }
  set_pc(7); if (d(ZNX_D32_COUNT - 1) != 7) { ok = false; }
  set_sup_mode(); if (d(ZNX_D32_COUNT - 1) != 7) { ok = false; }
  set_pc(1); if (d(ZNX_D32_COUNT - 1) != 1) { ok = false; }

  // Link register
  if (lr()) { ok = false; }
  set_lr(7); if (lr() != 7) { ok = false; }
  // User and supervisor link registers are distinct
  clr_sup_mode(); if (lr()) { ok = false; }
  set_lr(7); if (lr() != 7) { ok = false; }
  set_lr(0); if (lr()) { ok = false; }
  set_sup_mode(); if (lr() != 7) { ok = false; }
  set_lr(0); if (lr()) { ok = false; }

  // Test shared register
  if (lr()) { ok = false; }
  set_i(ZNX_I32_COUNT - 1, 7); if (lr() != 7) { ok = false; }
  // User and supervisor link registers are distinct
  clr_sup_mode(); if (lr()) { ok = false; }
  set_i(ZNX_I32_COUNT - 1, 7); if (lr() != 7) { ok = false; }
  set_i(ZNX_I32_COUNT - 1, 0); if (lr()) { ok = false; }
  set_sup_mode(); if (lr() != 7) { ok = false; }
  set_i(ZNX_I32_COUNT - 1, 0); if (lr()) { ok = false; }

  if (i(ZNX_I32_COUNT - 1)) { ok = false; }
  set_lr(7); if (i(ZNX_I32_COUNT - 1) != 7) { ok = false; }
  // User and supervisor link registers are distinct
  clr_sup_mode(); if (i(ZNX_I32_COUNT - 1)) { ok = false; }
  set_lr(7); if (i(ZNX_I32_COUNT - 1) != 7) { ok = false; }
  set_lr(0); if (i(ZNX_I32_COUNT - 1)) { ok = false; }
  set_sup_mode(); if (i(ZNX_I32_COUNT - 1) != 7) { ok = false; }
  set_lr(0); if (i(ZNX_I32_COUNT - 1)) { ok = false; }

  if (asn()) { ok = false; }
  set_asn(7); if (asn() != 7) { ok = false; }
  set_asn(0); if (asn() != 0) { ok = false; }
  std::cout << "register: alias registers................check: " << chok(ok);
}
