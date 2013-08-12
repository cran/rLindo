\name{rLSwriteIUS}
\alias{rLSwriteIUS}

\title{Writes the IUS of an unbounded LP to a file in LINDO file format.}

\description{
 R interface function for LINDO API function \code{LSwriteIUS}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSwriteIUS(model,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the file to which the IUS should be written.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSwriteIIS}}
}