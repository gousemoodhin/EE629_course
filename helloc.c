#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

int AddNumbers(int a, int b) { return a + b; }

/* Add function of the kernel symbol table */
EXPORT_SYMBOL(AddNumbers);

/* Init function of the kernel module */
static int ModuleHelloInsert(void) {
  printk("value = %d", AddNumbers(2, 3));

  printk(KERN_ALERT "Hello, world\n");
  return 0;
}

/* Exit function of the kernel module */
static void ModuleHelloExit(void) { printk(KERN_ALERT "Goodbye, world\n"); }

module_init(ModuleHelloInsert);  // Inform kernel init() function name
module_exit(ModuleHelloExit);    // Inform kernel Exit() function name
