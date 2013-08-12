\name{rLSwriteIIS}
\alias{rLSwriteIIS}

\title{Writes the IIS of an infeasible LP to a file in LINDO file format.}

\description{
 R interface function for LINDO API function \code{LSwriteIIS}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSwriteIIS(model,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the file to which the IIS should be written.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSwriteSolution}}
}