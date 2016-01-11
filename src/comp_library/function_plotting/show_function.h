//-*-C++-*-
// TODO: Merge empty else functions to fewer variadic template functions.

#ifndef SHOW_FUNCTION_H
#define SHOW_FUNCTION_H

class SHOW
{
public:

  template<typename scalar_type>
  static void plot_points(std::vector<scalar_type> x, std::vector<scalar_type> y);

  template<typename scalar_type>
  static void plot_points(Gnuplot& plot_obj, std::vector<scalar_type> x, std::vector<scalar_type> y);

  template<typename scalar_type>
  static void plot_points(Gnuplot& plot_obj, std::vector<scalar_type> x, std::vector<scalar_type> y, std::string name, std::string style);

  template<typename scalar_type>
  static void plot_points(std::vector<std::vector<scalar_type> >& elements, bool save_figure=false);

  template<typename scalar_type>
  static void plot_points(Gnuplot& plot_obj, std::vector<std::vector<scalar_type> >& elements);


  template<typename scalar_type>
  static void plot_line_2D(Gnuplot& plot_obj, std::vector<scalar_type> x, std::vector<scalar_type> y);

  template<typename scalar_type>
  static void plot_line_3D(Gnuplot& plot_obj, std::vector<scalar_type> x, std::vector<scalar_type> y);

  template<typename scalar_type, typename dmn_type>
  static void execute(FUNC_LIB::function<scalar_type, dmn_type>& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_0_type, typename dmn_1_type, typename dmn_2_type>
  static void plot_bandstructure(FUNC_LIB::function<scalar_type, dmn_2<dmn_2<dmn_0_type, dmn_1_type>, dmn_2_type> >& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_type>
  static void plot_data(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_type>
  static void plot_data(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_type>
  static void plot_data(Gnuplot& plot_obj, FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f);

  template<typename scalar_type, typename dmn_type>
  static void plot_data(Gnuplot& plot_obj, FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f);

  template<typename scalar_type, typename dmn_type>
  static void plot_data(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f,
                        FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& g,
                        bool save_figure=false);

  template<typename scalar_type, typename dmn_type>
  static void plot_error_bars(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f,
                              FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& g);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
  static void plot_error_bars(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f,
                              FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& g);

  template<typename scalar_type, typename dmn_type>
  static void execute(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_type>
  static void execute(Gnuplot& plot_obj, FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f);

  template<typename scalar_type, typename dmn_type>
  static void execute(Gnuplot& plot_obj, FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f);

  template<typename scalar_type, typename dmn_type>
  static void execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
  static void execute(FUNC_LIB::function<scalar_type, dmn_2<dmn_type_0, dmn_type_1> >& f, int n, bool save_figure=false);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
  static void execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_2<dmn_type_0, dmn_type_1> >& f, int n, bool save_figure=false);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
  static void execute(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
  static void execute_on_bands(FUNC_LIB::function<scalar_type, dmn_3<dmn_type_0, dmn_type_1, dmn_type_2> >& f);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
  static void execute_on_bands(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
  static void execute(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f,
                      FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& g);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
  static void execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f,
                      FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& g);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
  static void execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
  static void execute_on_bands(FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
  static void execute(FUNC_LIB::function<scalar_type, dmn_0<dmn_type_0> >& f,
                      FUNC_LIB::function<scalar_type, dmn_0<dmn_type_1> >& g,
                      bool save_figure=false);

  template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
  static void execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type_0> >& f,
                      FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type_1> >& g,
                      bool save_figure=false);

  //   template<typename scalar_type, typename dmn_type>
  //   static void contour(FUNC_LIB::function<scalar_type, dmn_type>& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_type>
  static void contour(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_type>
  static void contour(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_type>
  static void heatmap(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f, bool save_figure=false);

  template<typename scalar_type, typename dmn_type>
  static void heatmap(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f, bool save_figure=false);

  template<typename scalar_type>
  static void heatmap(std::vector<scalar_type> x, std::vector<scalar_type> y, std::vector<scalar_type> z, std::string name="no-name");

};

#ifdef ALLOW_GNUPLOT
template<typename scalar_type>
void SHOW::plot_points(std::vector<scalar_type> x, std::vector<scalar_type> y)
{
  Gnuplot plot_obj("points");

  plot_obj.plot_xy(x, y, "no-name");

  plot_obj.showonscreen();
}
#else
template<typename scalar_type>
void SHOW::plot_points(std::vector<scalar_type> /*x*/, std::vector<scalar_type> /*y*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type>
void SHOW::plot_points(Gnuplot& plot_obj, std::vector<scalar_type> x, std::vector<scalar_type> y)
{
  plot_obj.plot_xy(x, y, "no-name");
}
#else
template<typename scalar_type>
void SHOW::plot_points(Gnuplot& /*plot_obj*/, std::vector<scalar_type> /*x*/, std::vector<scalar_type> /*y*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type>
void SHOW::plot_points(Gnuplot& plot_obj, std::vector<scalar_type> x, std::vector<scalar_type> y, std::string name, std::string style)
{
  plot_obj.set_style(style);
  plot_obj.plot_xy(x, y, name);
}
#else
template<typename scalar_type>
void SHOW::plot_points(Gnuplot& /*plot_obj*/, std::vector<scalar_type> /*x*/, std::vector<scalar_type> /*y*/, std::string /*name*/, std::string /*style*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type>
void SHOW::plot_line_2D(Gnuplot& plot_obj, std::vector<scalar_type> x, std::vector<scalar_type> y)
{
  assert(x.size()==2);
  assert(y.size()==2);

  std::vector<double> x_list(2);
  std::vector<double> y_list(2);

  x_list[0] = x[0]; y_list[0] = x[1];
  x_list[1] = y[0]; y_list[1] = y[1];

  plot_obj.plot_xy(x_list, y_list);
}
#else
template<typename scalar_type>
void SHOW::plot_line_2D(Gnuplot& /*plot_obj*/, std::vector<scalar_type> /*x*/, std::vector<scalar_type> /*y*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type>
void SHOW::plot_line_3D(Gnuplot& plot_obj, std::vector<scalar_type> x, std::vector<scalar_type> y)
{
  assert(x.size()==3);
  assert(y.size()==3);

  std::vector<double> x_list(2);
  std::vector<double> y_list(2);
  std::vector<double> z_list(2);

  x_list[0] = x[0]; y_list[0] = x[1]; z_list[0] = x[2];
  x_list[1] = y[0]; y_list[1] = y[1]; z_list[1] = y[2];

  plot_obj.plot_xyz(x_list, y_list, z_list);
}
#else
template<typename scalar_type>
void SHOW::plot_line_3D(Gnuplot& /*plot_obj*/, std::vector<scalar_type> /*x*/, std::vector<scalar_type> /*y*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type>
void SHOW::plot_points(std::vector<std::vector<scalar_type> >& elements, bool /*save_figure*/)
{
  assert(elements[0].size()==2);

  std::vector<double> x(0);
  std::vector<double> y(0);

  for(size_t i=0; i<elements.size(); i++){
    x.push_back(elements[i][0]);
    y.push_back(elements[i][1]);

    //cout << x[i] << "\t" << y[i] << endl;
  }

  Gnuplot plot_obj("points");

  plot_obj.plot_xy(x, y, "no-name");

  plot_obj.showonscreen();

  //assert(false);
}
#else
template<typename scalar_type>
void SHOW::plot_points(std::vector<std::vector<scalar_type> >& /*elements*/, bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type>
void SHOW::plot_points(Gnuplot& plot_obj, std::vector<std::vector<scalar_type> >& elements)
{
  assert(elements[0].size()==2);

  std::vector<double> x(0);
  std::vector<double> y(0);

  for(size_t i=0; i<elements.size(); i++){
    x.push_back(elements[i][0]);
    y.push_back(elements[i][1]);

    //cout << x[i] << "\t" << y[i] << endl;
  }

  plot_obj.plot_xy(x, y);

  plot_obj.showonscreen();

  //assert(false);
}
#else
template<typename scalar_type>
void SHOW::plot_points(Gnuplot& /*plot_obj*/, std::vector<std::vector<scalar_type> >& /*elements*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_0_type, typename dmn_1_type, typename dmn_2_type>
void SHOW::plot_bandstructure(FUNC_LIB::function<scalar_type, dmn_2<dmn_2<dmn_0_type, dmn_1_type>, dmn_2_type> >& f, bool save_figure)
{
  Gnuplot plot_obj("lines");

  for(int i=0; i<dmn_0_type::dmn_size(); i++)
  {
    std::vector<double> x(0);
    std::vector<double> y(0);

    for(int j=0; j<dmn_2_type::dmn_size(); j++){
      x.push_back(j);
      y.push_back(f(i,j));
    }

    plot_obj.plot_xy(x, y, f.get_name());
  }

  //plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_0_type, typename dmn_1_type, typename dmn_2_type>
void SHOW::plot_bandstructure(FUNC_LIB::function<scalar_type, dmn_2<dmn_2<dmn_0_type, dmn_1_type>, dmn_2_type> >& /*f*/, bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f, bool save_figure)
{
  std::vector<double> x(0);
  std::vector<double> y(0);

  for(int i=0; i<f.size(); i++){
    x.push_back(i/double(f.size()));
    y.push_back(f(i));
  }

  Gnuplot plot_obj("lines");

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x, y, f.get_name());

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& /*f*/, bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f, bool save_figure)
{
  std::vector<double> x(0);
  std::vector<double> y(0);
  std::vector<double> z(0);

  for(int i=0; i<f.size(); i++){
    x.push_back(i/double(f.size()));
    y.push_back(real(f(i)));
    z.push_back(imag(f(i)));
  }

  Gnuplot plot_obj("lines");

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x, y, f.get_name());
  plot_obj.plot_xy(x, z, f.get_name());

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& /*f*/, bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(Gnuplot& plot_obj, FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f)
{
  std::vector<double> x(0);
  std::vector<double> y(0);

  for(int i=0; i<f.size(); i++){
    x.push_back(i/double(f.size()));
    y.push_back(f(i));
  }

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x, y, f.get_name());
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(Gnuplot& /*plot_obj*/, FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& /*f*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(Gnuplot& plot_obj, FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f)
{
  std::vector<double> x(0);
  std::vector<double> y(0);
  std::vector<double> z(0);

  for(int i=0; i<f.size(); i++){
    x.push_back(i/double(f.size()));
    y.push_back(real(f(i)));
    z.push_back(imag(f(i)));
  }

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x, y, f.get_name());
  plot_obj.plot_xy(x, z, f.get_name());
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(Gnuplot& /*plot_obj*/, FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& /*f*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f,
                     FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& g,
                     bool save_figure)
{
  std::vector<double> x(0);
  std::vector<double> f_re(0);
  std::vector<double> f_im(0);
  std::vector<double> g_re(0);
  std::vector<double> g_im(0);

  for(int i=0; i<f.size(); i++){
    x.push_back(i/double(f.size()));
    f_re.push_back(real(f(i)));
    f_im.push_back(imag(f(i)));
    g_re.push_back(real(g(i)));
    g_im.push_back(imag(g(i)));
  }

  Gnuplot plot_obj("points");

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x, f_re, f.get_name());
  plot_obj.plot_xy(x, f_im, f.get_name());
  plot_obj.plot_xy(x, g_re, g.get_name());
  plot_obj.plot_xy(x, g_im, g.get_name());

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::plot_data(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& /*f*/,
                     FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& /*g*/,
                     bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::plot_error_bars(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f,
                           FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& g)
{
  //cout << __FUNCTION__ << endl;

  std::vector<double>& x_points = dmn_type::get_elements();

  //Gnuplot plot_obj("linespoints");
  Gnuplot plot_obj("lines");

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  {
    std::vector<double> x(0);
    std::vector<double> y_re_1(0);
    std::vector<double> y_re_2(0);

    for(int i=0; i<dmn_type::get_size(); i++){
      x.push_back(x_points[i]);

      y_re_1.push_back(f(i));
      y_re_2.push_back(g(i));
    }

    plot_obj.set_style("lines");
    plot_obj.plot_xy_err(x, y_re_1, y_re_2, f.get_name());
  }

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::plot_error_bars(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& /*f*/,
                           FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& /*g*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::plot_error_bars(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f,
                           FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& g)
{
  //cout << __FUNCTION__ << endl;

  std::vector<double>& x_points = dmn_type_2::get_elements();

  //Gnuplot plot_obj("linespoints");
  Gnuplot plot_obj("lines");

  plot_obj.set_xlabel(dmn_type_2::parameter_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  for(int j=0; j<dmn_type_1::dmn_size(); j++){

    std::vector<double> x(0);
    std::vector<double> y_re_1(0);
    std::vector<double> y_re_2(0);

    for(int i=0; i<dmn_type_2::dmn_size(); i++){
      x.push_back(x_points[i]);

      y_re_1.push_back(f(0,0,j,i));
      y_re_2.push_back(g(0,0,j,i));
    }

    plot_obj.set_style("lines");
    plot_obj.plot_xy_err(x, y_re_1, y_re_2, f.get_name());
  }

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::plot_error_bars(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*f*/,
                           FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*g*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f, bool save_figure)
{
  std::vector<double>& x = dmn_type::get_elements();

  std::vector<double> y(0);
  for(int i=0; i<f.size(); i++)
    y.push_back(f(i));

  Gnuplot plot_obj("lines");
  //Gnuplot plot_obj("points");

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x, y, f.get_name());

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& /*f*/, bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::execute(Gnuplot& plot_obj, FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f)
{
  std::vector<double>& x = dmn_type::get_elements();

  std::vector<double> y(0);
  for(int i=0; i<f.size(); i++)
    y.push_back(f(i));

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x, y, f.get_name());

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::execute(Gnuplot& /*plot_obj*/, FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& /*f*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::execute(Gnuplot& plot_obj, FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f)
{
  std::vector<double>& x = dmn_type::get_elements();

  std::vector<double> y_re(0);
  for(int i=0; i<f.size(); i++)
    y_re.push_back(real(f(i)));

  std::vector<double> y_im(0);
  for(int i=0; i<f.size(); i++)
    y_im.push_back(imag(f(i)));

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x, y_re, "Re["+f.get_name()+"]");
  plot_obj.plot_xy(x, y_im, "Im["+f.get_name()+"]");

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::execute(Gnuplot& /*plot_obj*/, FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& /*f*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f,
                   bool save_figure)
{
  std::vector<double>& x = dmn_type::get_elements();

  std::vector<double> y_re(0);
  std::vector<double> y_im(0);
  for(int i=0; i<f.size(); i++)
  {
    y_re.push_back(real(f(i)));
    y_im.push_back(imag(f(i)));
  }

  Gnuplot plot_obj("lines");

  plot_obj.set_xlabel(dmn_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x, y_re, "");
  plot_obj.plot_xy(x, y_im, "");

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& /*f*/,
                   bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_2<dmn_type_0, dmn_type_1> >& f, int n, bool save_figure)
{
  Gnuplot plot_obj("lines");

  std::vector<double> x;
  if(n==0)
  {
    //x = dmn_type_0::get_elements();
    plot_obj.set_xlabel(dmn_type_0::get_name());
  }
  else
  {
    x = dmn_type_1::get_elements();
    plot_obj.set_xlabel(dmn_type_1::get_name());
  }

  plot_obj.set_ylabel(f.get_name());

  if(n==0)
  {
    for(int j=0; j<f[1]; j++)
    {
      std::vector<double> y_re(0);
      //std::vector<double> y_im(0);
      for(int i=0; i<f[0]; i++)
      {
        y_re.push_back((f(i,j)));
        //y_im.push_back(imag(f(i,j)));
      }

      plot_obj.plot_xy(x, y_re, "");
      //plot_obj.plot_xy(x, y_im, "");
    }
  }
  else
  {
    for(int j=0; j<f[0]; j++)
    {
      std::vector<double> y_re(0);
      //std::vector<double> y_im(0);
      for(int i=0; i<f[1]; i++)
      {
        y_re.push_back((f(j,i)));
        //y_im.push_back(imag(f(j,i)));
      }

      plot_obj.plot_xy(x, y_re, "");
      //plot_obj.plot_xy(x, y_im, "");
    }
  }

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_2<dmn_type_0, dmn_type_1> >& /*f*/, int /*n*/, bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_2<dmn_type_0, dmn_type_1> >& f, int n, bool save_figure)
{
  Gnuplot plot_obj("lines");

  std::vector<double> x;
  if(n==0)
  {
    //x = dmn_type_0::get_elements();
    plot_obj.set_xlabel(dmn_type_0::get_name());
  }
  else
  {
    x = dmn_type_1::get_elements();
    plot_obj.set_xlabel(dmn_type_1::get_name());
  }

  plot_obj.set_ylabel(f.get_name());

  if(n==0)
  {
    for(int j=0; j<f[1]; j++)
    {
      std::vector<double> y_re(0);
      std::vector<double> y_im(0);
      for(int i=0; i<f[0]; i++)
      {
        y_re.push_back(real(f(i,j)));
        y_im.push_back(imag(f(i,j)));
      }

      plot_obj.plot_xy(x, y_re, "");
      plot_obj.plot_xy(x, y_im, "");
    }
  }
  else
  {
    for(int j=0; j<f[0]; j++)
    {
      std::vector<double> y_re(0);
      std::vector<double> y_im(0);
      for(int i=0; i<f[1]; i++)
      {
        y_re.push_back(real(f(j,i)));
        y_im.push_back(imag(f(j,i)));
      }

      plot_obj.plot_xy(x, y_re, "");
      plot_obj.plot_xy(x, y_im, "");
    }
  }

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_2<dmn_type_0, dmn_type_1> >& /*f*/, int /*n*/, bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f)
{
  std::vector<double>& x_points = dmn_type_2::get_elements();

  Gnuplot plot_obj("linespoints");

  plot_obj.set_xlabel(dmn_type_2::parameter_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  for(int j=0; j<dmn_type_1::dmn_size(); j++){

    std::vector<double> x(0);
    std::vector<double> y_re(0);
    std::vector<double> y_im(0);

    for(int i=std::max(dmn_type_2::dmn_size()/2-32,0); i<std::min(dmn_type_2::dmn_size()/2+32, dmn_type_2::dmn_size()); i++){
      //for(int i=0; i<dmn_type_2::dmn_size(); i++){

      x.push_back(x_points[i]);

      y_re.push_back(real(f(0,0,j,i)));
      y_im.push_back(imag(f(0,0,j,i)));
    }

    plot_obj.plot_xy(x, y_re, "");
    plot_obj.plot_xy(x, y_im, "");
  }

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*f*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute_on_bands(FUNC_LIB::function<scalar_type, dmn_3<dmn_type_0, dmn_type_1, dmn_type_2> >& f)
{
  Gnuplot plot_obj("linespoints");

  std::vector<double>& x_points = dmn_type_2::get_elements();

  for(int j=0; j<dmn_type_0::dmn_size(); j++){

    plot_obj.set_xlabel(dmn_type_2::parameter_type::get_name());
    plot_obj.set_ylabel(f.get_name());

    std::vector<double> x(0);
    std::vector<double> y_re(0);

    //for(int i=std::max(dmn_type_2::dmn_size()/2-32,0); i<std::min(dmn_type_2::dmn_size()/2+32, dmn_type_2::dmn_size()); i++){
    for(int i=0; i<dmn_type_2::dmn_size(); i++){

      x.push_back(x_points[i]);

      y_re.push_back(f(j,0,i));
    }

    plot_obj.plot_xy(x, y_re, "");
  }

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute_on_bands(FUNC_LIB::function<scalar_type, dmn_3<dmn_type_0, dmn_type_1, dmn_type_2> >& /*f*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute_on_bands(FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f)
{
  int shift = dmn_type_2::dmn_size()/2;

  Gnuplot plot_obj("linespoints");

  std::vector<double>& x_points = dmn_type_2::get_elements();

  for(int j=0; j<dmn_type_0::dmn_size()/2; j++){

    plot_obj.set_xlabel(dmn_type_2::parameter_type::get_name());
    plot_obj.set_ylabel(f.get_name());

    std::vector<double> x(0);
    std::vector<double> y_re(0);
    std::vector<double> y_im(0);

    //for(int i=std::max(dmn_type_2::dmn_size()/2-32,0); i<std::min(dmn_type_2::dmn_size()/2+32, dmn_type_2::dmn_size()); i++){
    for(int i=std::max(0,dmn_type_2::dmn_size()/2-shift); i<std::min(dmn_type_2::dmn_size(), dmn_type_2::dmn_size()/2+shift); i++){

      x.push_back(x_points[i]);

      y_re.push_back(real(f(j,j,0,i)));
      y_im.push_back(imag(f(j,j,0,i)));
    }

    plot_obj.plot_xy(x, y_re, "");
    plot_obj.plot_xy(x, y_im, "");
  }

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute_on_bands(FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*f*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f)
{
  std::cout << __FUNCTION__ << std::endl;

  std::vector<double>& x_points = dmn_type_2::get_elements();

  Gnuplot plot_obj("linespoints");
  //Gnuplot plot_obj("lines");

  plot_obj.set_xlabel(dmn_type_2::parameter_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  for(int j=0; j<dmn_type_1::dmn_size(); j++){

    std::vector<double> x(0);
    std::vector<double> y_re(0);

    for(int i=0; i<dmn_type_2::dmn_size(); i++){
      x.push_back(x_points[i]);

      y_re.push_back(f(0,0,j,i));

      //cout << x_points[i] << "\t" << f(0,0,j,i) << endl;
    }

    plot_obj.plot_xy(x, y_re, f.get_name());
  }

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*f*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute_on_bands(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f)
{
  Gnuplot plot_obj("linespoints");

  std::vector<double>& x_points = dmn_type_2::get_elements();

  for(int j=0; j<dmn_type_0::dmn_size()/2; j++){


    //Gnuplot plot_obj("lines");

    plot_obj.set_xlabel(dmn_type_2::parameter_type::get_name());
    plot_obj.set_ylabel(f.get_name());

    std::vector<double> x(0);
    std::vector<double> y_re(0);

    for(int i=0; i<dmn_type_2::dmn_size(); i++){
      x.push_back(x_points[i]);

      y_re.push_back(f(j,j,0,i));

      //cout << x_points[i] << "\t" << f(0,0,j,i) << endl;
    }

    plot_obj.plot_xy(x, y_re, f.get_name());
  }

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute_on_bands(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*f*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f,
                   FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& g)
{
  //cout << __FUNCTION__ << endl;

  std::vector<double>& x_points = dmn_type_2::get_elements();

  //Gnuplot plot_obj("linespoints");
  Gnuplot plot_obj("lines");

  plot_obj.set_xlabel(dmn_type_2::parameter_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  for(int j=0; j<dmn_type_1::dmn_size(); j++){

    std::vector<double> x(0);
    std::vector<double> y_re_1(0);
    std::vector<double> y_re_2(0);

    for(int i=0; i<dmn_type_2::dmn_size(); i++){
      x.push_back(x_points[i]);

      y_re_1.push_back(f(0,0,j,i));
      y_re_2.push_back(g(0,0,j,i));
    }

    plot_obj.set_style("lines");
    plot_obj.plot_xy(x, y_re_1, f.get_name());
    plot_obj.set_style("points");
    plot_obj.plot_xy(x, y_re_2, g.get_name());
  }

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*f*/,
                   FUNC_LIB::function<scalar_type, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*g*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& f,
                   FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& g)
{
  std::cout << __FUNCTION__ << std::endl;

  std::vector<double>& x_points = dmn_type_2::get_elements();

  //Gnuplot plot_obj("linespoints");
  Gnuplot plot_obj("lines");

  plot_obj.set_xlabel(dmn_type_2::parameter_type::get_name());
  plot_obj.set_ylabel(f.get_name());

  for(int j=0; j<dmn_type_1::dmn_size(); j++){

    std::vector<double> x(0);
    std::vector<double> y_re_1(0);
    std::vector<double> y_re_2(0);
    std::vector<double> y_im_1(0);
    std::vector<double> y_im_2(0);

    for(int i=0; i<dmn_type_2::dmn_size(); i++){
      x.push_back(x_points[i]);

      y_re_1.push_back(real(f(0,0,j,i)));
      y_re_2.push_back(real(g(0,0,j,i)));

      y_im_1.push_back(imag(f(0,0,j,i)));
      y_im_2.push_back(imag(g(0,0,j,i)));
    }

    plot_obj.set_style("lines");
    plot_obj.plot_xy(x, y_re_1, f.get_name());
    plot_obj.plot_xy(x, y_im_1, f.get_name());
    plot_obj.set_style("points");
    plot_obj.plot_xy(x, y_re_2, g.get_name());
    plot_obj.plot_xy(x, y_im_2, g.get_name());
  }

  plot_obj.showonscreen();
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1, typename dmn_type_2>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*f*/,
                   FUNC_LIB::function<std::complex<scalar_type>, dmn_4<dmn_type_0, dmn_type_0, dmn_type_1, dmn_type_2> >& /*g*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_0<dmn_type_0> >& f,
                   FUNC_LIB::function<scalar_type, dmn_0<dmn_type_1> >& g,
                   bool save_figure)
{
  std::vector<double>& x_0 = dmn_type_0::get_elements();
  std::vector<double>& x_1 = dmn_type_1::get_elements();

  std::vector<double> f_re(0);
  std::vector<double> g_re(0);

  for(int i=0; i<f.size(); i++)
    f_re.push_back((f(i)));

  for(int i=0; i<g.size(); i++)
    g_re.push_back((g(i)));

  Gnuplot plot_obj("points");

  plot_obj.set_xlabel(dmn_type_0::get_name());
  //plot_obj.set_ylabel(f.get_name());

  plot_obj.set_style("lines");
  plot_obj.plot_xy(x_0, f_re, f.get_name());

  plot_obj.set_style("points");
  plot_obj.plot_xy(x_1, g_re, g.get_name());

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
void SHOW::execute(FUNC_LIB::function<scalar_type, dmn_0<dmn_type_0> >& /*f*/,
                   FUNC_LIB::function<scalar_type, dmn_0<dmn_type_1> >& /*g*/,
                   bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type_0> >& f,
                   FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type_1> >& g,
                   bool save_figure)
{
  std::vector<double>& x_0 = dmn_type_0::get_elements();
  std::vector<double>& x_1 = dmn_type_1::get_elements();

  std::vector<double> f_re(0);
  std::vector<double> f_im(0);

  for(int i=0; i<f.size(); i++)
  {
    f_re.push_back(real(f(i)));
    f_im.push_back(imag(f(i)));
  }

  std::vector<double> g_re(0);
  std::vector<double> g_im(0);

  for(int i=0; i<g.size(); i++)
  {
    g_re.push_back(real(g(i)));
    g_im.push_back(imag(g(i)));
  }

  Gnuplot plot_obj("lines");
  //Gnuplot plot_obj("points");

  plot_obj.set_xlabel(dmn_type_0::get_name());
  //plot_obj.set_ylabel(f.get_name());

  plot_obj.plot_xy(x_0, f_re, "Re["+f.get_name()+"]");
  plot_obj.plot_xy(x_0, f_im, "Im["+f.get_name()+"]");

  plot_obj.plot_xy(x_1, g_re, "Re["+g.get_name()+"]");
  plot_obj.plot_xy(x_1, g_im, "Im["+g.get_name()+"]");

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type_0, typename dmn_type_1>
void SHOW::execute(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type_0> >& /*f*/,
                   FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type_1> >& /*g*/,
                   bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::contour(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f, bool save_figure)
{
  std::vector<std::vector<double> >& vecs = dmn_type::get_elements();

  std::vector<double> x(0);
  std::vector<double> y(0);
  std::vector<double> z(0);

  for(int i=0; i<f.size(); i++)
  {
    x.push_back(vecs[i][0]);
    y.push_back(vecs[i][1]);
    z.push_back(f(i));
  }

  Gnuplot plot_obj("lines");

  plot_obj.plot_xyz(x, y, z, f.get_name());

  plot_obj << "set dgrid3d  100,100,16";

  plot_obj.set_isosamples(10).set_contour("base");

  plot_obj << "set dgrid3d";
  plot_obj << "unset surface";
  plot_obj << "set view map";
  plot_obj << "set cntrparam levels 20";
  plot_obj.replot();

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::contour(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& /*f*/, bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::heatmap(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f, bool save_figure)
{
  std::vector<std::vector<double> >& vecs = dmn_type::get_elements();

  std::vector<double> x(0);
  std::vector<double> y(0);
  std::vector<double> z(0);

  for(int i=0; i<f.size(); i++)
  {
    x.push_back(vecs[i][0]);
    y.push_back(vecs[i][1]);
    z.push_back(f(i));
  }

  Gnuplot plot_obj("lines");

  plot_obj << "set dgrid3d  100,100,16";
  plot_obj << "set pm3d at b";

  plot_obj.plot_xyz(x, y, z, f.get_name());

  plot_obj << "unset surface";
  plot_obj << "set pm3d map";

  //plot_obj << "set palette gray";

  plot_obj.replot();

  plot_obj.showonscreen();

  if(save_figure)
    plot_obj.savetops(f.get_name());
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::heatmap(FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& /*f*/, bool /*save_figure*/)
{}
#endif

/*
  template<typename scalar_type, typename dmn_type>
  void SHOW::heatmap(Gnuplot& plot_obj, FUNC_LIB::function<scalar_type, dmn_0<dmn_type> >& f)
  {
  #ifdef ALLOW_GNUPLOT

  std::vector<std::vector<double> >& vecs = dmn_type::get_elements();

  std::vector<double> x(0);
  std::vector<double> y(0);
  std::vector<double> z(0);

  for(int i=0; i<f.size(); i++)
  {
  x.push_back(vecs[i][0]);
  y.push_back(vecs[i][1]);
  z.push_back(f(i));
  }

  //Gnuplot plot_obj("lines");

  plot_obj << "set dgrid3d  100,100,16";
  plot_obj << "set pm3d at b";

  plot_obj.plot_xyz(x, y, z, f.get_name());

  plot_obj << "unset surface";
  plot_obj << "set pm3d map";

  //plot_obj << "set palette gray";

  plot_obj.replot();

  plot_obj.showonscreen();

  if(save_figure)
  plot_obj.savetops(f.get_name());

  #endif
  }
*/

#ifdef ALLOW_GNUPLOT
template<typename scalar_type, typename dmn_type>
void SHOW::heatmap(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& f, bool /*save_figure*/)
{
  FUNC_LIB::function<scalar_type, dmn_0<dmn_type> > f_re("Re["+f.get_name()+"]");
  FUNC_LIB::function<scalar_type, dmn_0<dmn_type> > f_im("Im["+f.get_name()+"]");

  for(int i=0; i<f.size(); i++)
  {
    f_re(i) = real(f(i));
    f_im(i) = imag(f(i));
  }

  heatmap(f_re);
  heatmap(f_im);
}
#else
template<typename scalar_type, typename dmn_type>
void SHOW::heatmap(FUNC_LIB::function<std::complex<scalar_type>, dmn_0<dmn_type> >& /*f*/, bool /*save_figure*/)
{}
#endif

#ifdef ALLOW_GNUPLOT
template<typename scalar_type>
void SHOW::heatmap(std::vector<scalar_type> x, std::vector<scalar_type> y, std::vector<scalar_type> z, std::string name)
{
  Gnuplot plot_obj("lines");

  plot_obj << "set dgrid3d  100,100,16";
  plot_obj << "set pm3d at b";

  plot_obj.plot_xyz(x, y, z, name);

  plot_obj << "unset surface";
  plot_obj << "set pm3d map";

  //plot_obj << "set palette gray";

  plot_obj.replot();

  plot_obj.showonscreen();
}
#else
template<typename scalar_type>
void SHOW::heatmap(std::vector<scalar_type> /*x*/, std::vector<scalar_type> /*y*/, std::vector<scalar_type> /*z*/, std::string /*name*/)
{}
#endif

#endif
