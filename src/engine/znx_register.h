// register counts
#define ZNX_I32_COUNT 16
#define ZNX_D32_COUNT 16
#define ZNX_F64_COUNT 16
#define ZNX_SIMD_DEPTH 8 // x32 = 256-bit
#define ZNX_SIMD_COUNT 4

class znx_register {
  bool s_mode;

  // Status register flags for user mode:
  bool u_zero, u_neg, u_oflow, u_carry,
    u_fzero, u_fneg, u_inf, u_neg_inf, u_nan, u_denorm;

  // Status registers for supervisor mode:
  bool s_zero, s_neg, s_oflow, s_carry,
    s_fzero, s_fneg, s_inf, s_neg_inf, s_nan, s_denorm;

  // Main integer registers
  unsigned int *_i;
  unsigned int *_d;

  // Supervisor integer registers (%if = %pc = common)
  unsigned int *_si;
  unsigned int *_sd;

  // Floating point registers
  double *_f;

  // SIMD registers
  unsigned int **_m;

  // ASN register
  unsigned int _asn;

public:
  znx_register();

  // Supervisor mode:
  bool sup_mode();
  void set_sup_mode();
  void clr_sup_mode();

  // Status flags:
  bool zero();
  bool neg();
  bool oflow();
  bool carry();
  bool fzero();
  bool fneg();
  bool inf();
  bool neg_inf();
  bool nan();
  bool denorm();

  // Set status flags:
  void set_zero();
  void set_neg();
  void set_oflow();
  void set_carry();
  void set_fzero();
  void set_fneg();
  void set_inf();
  void set_neg_inf();
  void set_nan();
  void set_denorm();

  // Clear status flags:
  void clr_zero();
  void clr_neg();
  void clr_oflow();
  void clr_carry();
  void clr_fzero();
  void clr_fneg();
  void clr_inf();
  void clr_neg_inf();
  void clr_nan();
  void clr_denorm();

  unsigned int status();
  void set_status(unsigned int value);

  // Register access
  unsigned int i(int index);
  void set_i(int index, unsigned int value);

  unsigned int d(int index);
  void set_d(int index, unsigned int value);

  double f(int index);
  void set_f(int index, double value);

  // TODO: encapsulate vector registers with something a bit more robust
  // Not a copy, this is original array (do not free)
  unsigned int* m(int index);
  // Copy passed data into register (free after setting)
  void set_m(int index, unsigned int* value);

  unsigned int sp();
  void set_sp(unsigned int value);

  unsigned int pc();
  void set_pc(unsigned int value);
  
  unsigned int lr();
  void set_lr(unsigned int value);

  unsigned int asn();
  void set_asn(unsigned int value);

  void system_check();
};
