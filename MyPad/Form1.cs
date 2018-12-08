using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;


namespace EncReader
{
    public partial class EncReader : Form
    {
      
        public EncReader()
        {
            InitializeComponent();
        }
    
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog1.FileName;
                string text="";
                if ( Program.ReadFile(filePath, ref text))
                {
                    editor.Text = text;
                    string fileName = Path.GetFileName(filePath);
                    this.Text = fileName;
                    this.Update();
                }
                else
                {
                    MessageBox.Show(text,"Error");
                }
            }
        }

        private void SaveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string text = editor.Text;
            if (text.Length == 0)
                return;
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string filePath = saveFileDialog1.FileName;
                
                if(Program.WriteFile(filePath, ref text))
                {
                    string fileName = Path.GetFileName(filePath);
                    this.Text = fileName;
                    this.Update();
                }
                else
                {
                    MessageBox.Show(text, "Error");
                }
            }            
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void saveToolStripMenuItem_Click_1(object sender, EventArgs e)
        {

        }

        private void fontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fontDialog1.ShowDialog() != DialogResult.Cancel)
            {
                editor.Font = fontDialog1.Font;
            }
        }
    }
}
