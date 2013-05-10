package java.io;

public class StringWriter extends Writer
{
	private final StringBuffer sb;

	public StringWriter()
	{
		this.sb = new StringBuffer();
	}

	public StringWriter(int size)
	{
		this.sb = new StringBuffer(size);
	}


	public void close() throws IOException
	{
		//nothing
	}


	public void flush() throws IOException
	{
		//nothing
	}

	public StringBuffer getBuffer()
	{
		return this.sb;
	}


	public String toString()
	{
		return this.sb.toString();
	}


	public Writer append(CharSequence str, int start, int end) throws IOException
	{
		this.sb.append(str, start, end);
		return this;
	}


	public void write(int c) throws IOException
	{
		this.sb.append((char)c);
	}


	public void write(char[] c, int off, int len) throws IOException
	{
		this.sb.append(c, off, len);
	}


	public void write(String str, int off, int len) throws IOException
	{
		this.sb.append(str, off, off + len);
	}


}
