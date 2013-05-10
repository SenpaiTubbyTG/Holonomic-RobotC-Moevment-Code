package java.io;

public class FilterInputStream extends InputStream
{
	protected InputStream in;

	public FilterInputStream(InputStream in)
	{
		this.in = in;
	}


	public int available() throws IOException
	{
		return this.in.available();
	}


	public void close() throws IOException
	{
		this.in.close();
	}


	public void mark(int readAheadLimit)
	{
		this.in.mark(readAheadLimit);
	}


	public int read() throws IOException
	{
		return this.in.read();
	}


	public int read(byte[] b, int off, int len) throws IOException
	{
		return this.in.read(b, off, len);
	}


	public void reset() throws IOException
	{
		this.in.reset();
	}


	public long skip(long n) throws IOException
	{
		return this.in.skip(n);
	}
}
