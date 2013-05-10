package java.io;

public class FilterOutputStream extends OutputStream
{
	protected OutputStream out;

	public FilterOutputStream(OutputStream out)
	{
		this.out = out;
	}


	public void close() throws IOException
	{
		try
		{
			this.flush();
		}
		finally
		{
			this.out.close();
		}
	}


	public void flush() throws IOException
	{
		this.out.flush();
	}


	public void write(int b) throws IOException
	{
		this.out.write(b);
	}


	public void write(byte[] b, int off, int len) throws IOException
	{
		this.out.write(b, off, len);
	}
}
