\name{rLSwriteDeteqLINDOFile}
\alias{rLSwriteDeteqLINDOFile}

\title{Write the deterministic equivalent (DEQ) of the SP models in LINDO format.}

\description{
 R interface function for LINDO API function \code{LSwriteDeteqLINDOFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSwriteDeteqLINDOFile(model,pszFilename,iType)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFilename}{Path and name of the MPS file.}
 \item{iType}{Type of the the deterministic equivalent. Possible values are:
                   \itemize{
                        \item{LS_DETEQ_IMPLICIT}
                        \item{LS_DETEQ_EXPLICIT (default)}
                   }
               }
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSwriteDeteqMPSFile}}
}
