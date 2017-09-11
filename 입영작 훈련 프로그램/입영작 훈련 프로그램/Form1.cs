using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 입영작_훈련_프로그램
{
    public partial class Form1 : Form
    {
        Selecter selecter;
        Set now;
        public Form1()
        {
            InitializeComponent();
            var Start = new LibraryBuilder();
            selecter = new Selecter(Start);

            now = selecter.SelectSentence();
            label1.Text = now.kor;
            label2.Text = " ";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            now = selecter.SelectSentence();
            label1.Text = now.kor;
            label2.Text = " ";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label2.Text = now.eng;
        }
    }
}
