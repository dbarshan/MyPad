using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing;

namespace EncReader
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new EncReader());
        }
        
        public static bool ReadFile(string filePath, ref string text)
        {
            bool ret;
            try
            {
                using (BinaryReader br = new BinaryReader(new FileStream(filePath, FileMode.Open)))
                {
                    char[] charArray = br.ReadString().ToCharArray();
                    text = new string(charArray);
                    br.Close();
                    ret = true;
                }
            }
            catch (IOException ex)
            {
                text = ex.Message;
                ret = false;
            }
            return ret;
        }

        public static bool WriteFile(string filePath, ref string text)
        {
            bool ret;
            try
            {

                using (BinaryWriter binWriter = new BinaryWriter(new FileStream(filePath, FileMode.Create)))
                {
                    char[] charArray = text.ToCharArray();
                    binWriter.Write(new string(charArray));
                    ret = true;
                }
            }
            catch (Exception ex)
            {
                text = ex.Message;
                ret = false;
            }
            return ret;
        }

    }
}
